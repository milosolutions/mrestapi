#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class TestRestRequest : public QObject
{
    Q_OBJECT

public:
    TestRestRequest();
    ~TestRestRequest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

TestRestRequest::TestRestRequest()
{

}

TestRestRequest::~TestRestRequest()
{

}

void TestRestRequest::initTestCase()
{

}

void TestRestRequest::cleanupTestCase()
{

}

void TestRestRequest::test_case1()
{

}

QTEST_MAIN(TestRestRequest)

#include "tst_restrequest.moc"
