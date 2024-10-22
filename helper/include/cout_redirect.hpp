#pragma once

#include <thread>

class cout_redirect
{
public:
    explicit cout_redirect(std::ostringstream& buffer);
    ~cout_redirect();

private:
    std::ostringstream& m_buffer;
    int m_pipefd[2] = {-1, -1};
    int m_original_stdout_fd = {};
    bool m_is_active = {};
    std::thread m_reader_thread;

    void readPipe() const;
};