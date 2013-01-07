#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TextTestProgressListener.h>
#include <fstream>
#include <iostream>

namespace
{
    const char *const OUTPUT_FILENAME = "util_test.xml";
}

int main()
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestResult controller;
    CppUnit::TextTestProgressListener progressListener;
    CppUnit::TestResultCollector result;
    controller.addListener(&result);
    controller.addListener(&progressListener);
    std::ofstream xmlout(OUTPUT_FILENAME);
    CppUnit::XmlOutputter xmlOutputter(&result, xmlout); 
    CppUnit::TextOutputter consoleOutputter(&result, std::cout);

    CppUnit::TestFactoryRegistry &registry =
        CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    runner.run(controller);

    xmlOutputter.write();
    consoleOutputter.write();

    return !result.wasSuccessful();
}
