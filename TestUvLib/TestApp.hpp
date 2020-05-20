#ifndef TESTAPP_HPP
#define TESTAPP_HPP

#include "SingletonT.h"
#include "appnetstack.h" // Base class: IAppStart

class TestApp : public IAppStart, public SingletonT<TestApp>
{
public:
    TestApp();
    ~TestApp();

public:
    bool AllowExit(AppNetStack* ans) override;

    bool Init(int argv, char* argc[], AppNetStack* ans) override;

    bool OnExit(AppNetStack* ans) override;

    bool OnstackStart(AppNetStack* ans) override;

    bool StartWork(AppNetStack* ans) override;
    void DoStop()  override;
};

#endif // TESTAPP_HPP
