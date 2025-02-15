class ErrorSystem
{
private:
    std::string message;

public:
    ErrorSystem() {}

    void NewError(const std::string &msg)
    {
        this->message = msg;
    }

    std::string ErrorMessage()
    {
        return this->message;
    }

    bool GetErrors()
    {
        return !message.empty();
    }
};