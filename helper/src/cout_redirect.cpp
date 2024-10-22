#include "cout_redirect.hpp"

#include <sstream>
#include <unistd.h>

cout_redirect::cout_redirect(std::ostringstream& buffer) : m_buffer(buffer)
{
    // Create pipe
    if(pipe(m_pipefd) != 0)
    {
        throw std::runtime_error("Failed to create pipe");
    }

    // Save the original stdout file descriptor
    m_original_stdout_fd = dup(STDOUT_FILENO);
    if(m_original_stdout_fd == -1)
    {
        throw std::runtime_error("Failed to duplicate stdout");
    }

    // Redirect stdout to the write end of the pipe
    if(dup2(m_pipefd[1], STDOUT_FILENO) == -1)
    {
        throw std::runtime_error("Failed to redirect stdout to the pipe");
    }

    // Close the duplicated write end as it's now duplicated to stdout
    close(m_pipefd[1]);

    m_is_active = true;

    m_reader_thread = std::thread(&cout_redirect::readPipe, this);
}

cout_redirect::~cout_redirect()
{
    if(!m_is_active)
    {
        return;
    }
    // Flush stdout to ensure all output is written
    fflush(stdout);

    // Restore the original stdout
    dup2(m_original_stdout_fd, STDOUT_FILENO);
    close(m_original_stdout_fd);

    m_is_active = false;

    close(m_pipefd[0]);

    if (m_reader_thread.joinable())
    {
        m_reader_thread.join();
    }
}

void cout_redirect::readPipe() const
{
    char buffer[4096];
    ssize_t count;
    while (m_is_active && (count = read(m_pipefd[0], buffer, sizeof(buffer))) > 0) {
        m_buffer.write(buffer, count);
    }
}
