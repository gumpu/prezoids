#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include "ut.h"
#include "test_tiles.h"
#include "test_polygons.h"

class UTestCase {
    public:
        UTestCase();
        UTestCase(
                voidfunc_t* setup_function,
                voidfunc_t* test_function,
                voidfunc_t* teardown_function,
                const char* function_name,
                const char* label
                );
        ~UTestCase();
        UTestCase(const UTestCase& source);
        UTestCase& operator=(const UTestCase& source);

        voidfunc_t* m_setup_function; /*!< Function to be called before test function is called */
        voidfunc_t* m_test_function; /*!< The function that contains all tests */
        voidfunc_t* m_teardown_function; /*!< Function to be called after test function is called */
        std::string m_function_name;
        std::string m_label;
};


UTestCase::UTestCase(const UTestCase& source)
    : m_setup_function(source.m_setup_function), m_test_function(source.m_test_function),
    m_teardown_function(source.m_teardown_function), m_function_name(source.m_function_name),
    m_label(source.m_label)
{ }

UTestCase::UTestCase(
        voidfunc_t* setup_function,
        voidfunc_t* test_function,
        voidfunc_t* teardown_function,
        const char* function_name,
        const char* label
        )
    : m_setup_function(setup_function), m_test_function(test_function),
    m_teardown_function(teardown_function), m_function_name(function_name), m_label(label)
{ }

UTestCase::UTestCase()
    : m_setup_function(NULL), m_test_function(NULL), m_teardown_function(NULL),
    m_function_name(), m_label()
{ }

UTestCase::~UTestCase() { }

std::vector<UTestCase> g_test_cases;

void URegister(
        voidfunc_t* setup, voidfunc_t* teardown, voidfunc_t* test,
        const char* function_name, const char* label)
{
    g_test_cases.push_back(UTestCase(setup, test, teardown, function_name, label));
}

void UOrigAssert(const char* filename, uint32_t linenumber, bool value)
{
    if (!value) {
        printf("UAssert failed at file %s line %d\n", filename, linenumber);
    }
}
static void URunCase(UTestCase* test_case)
{
    printf("Test: %s\n", test_case->m_label.c_str());
    if (test_case->m_setup_function != NULL) {
        test_case->m_setup_function();
    }
    test_case->m_test_function();
    if (test_case->m_teardown_function != NULL) {
        test_case->m_teardown_function();
    }
    printf("Done: %s\n", test_case->m_label.c_str());
}

static void URunAll(int argc, char** argv)
{
    uint32_t i;
    if (argc > 1) {
        if (strcmp(argv[1], "list") == 0) {
            for (i = 0U;  i < g_test_cases.size(); i++) {
                printf("test: %s, label: %s\n",
                        g_test_cases[i].m_function_name.c_str(), g_test_cases[i].m_label.c_str());
            }
        } else {
            if (argc > 2) {
                if (strcmp(argv[1], "run") == 0) {
                    for (i = 0U;  i < g_test_cases.size(); i++) {
                        if (strcmp(g_test_cases[i].m_function_name.c_str(), argv[2]) == 0) {
                            URunCase(&(g_test_cases[i]));
                            break;
                        }
                    }
                }
            }
        }
    } else {
        printf("Test count: %ld\n", g_test_cases.size());
        for (i = 0U;  i < g_test_cases.size(); i++) {
            URunCase(&(g_test_cases[i]));
        }
        printf("Tests done: %d\n", i);
    }
}

int main(int argc, char** argv)
{
    register_tiles_tests();
    register_polygon_tests();

    if (g_test_cases.size() > 0) {
        URunAll(argc, argv);
    }

    return EXIT_SUCCESS;
}

/* ------------------------ end of file -------------------------------*/
