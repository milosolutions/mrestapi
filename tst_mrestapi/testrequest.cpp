#include "testrequest.h"

TestRequest::TestRequest(const QUrl &url) : MRestRequest(url)
{
    m_type = MRestRequest::Type::Get;
    m_priority = Priority::High;
}

// Intentionally empty
void TestRequest::parse()
{
    return;
}
