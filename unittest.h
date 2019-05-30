#ifndef UNITTEST_H
#define UNITTEST_H
/**
 *  @file   unittest.h
 *
 *  @brief  routines for unit test
 *
 *  @note   Test for strings uses strcmp. A include<string.h> is mandatory.
 *  @note   Uses C99 declaration of variables inside block.
 *
 *  @author Hans
 *  @date   21/04/2019
 */

/// Prefix for global variables
#define TESTPREFIX unit

/// Concatenate operator for C preprocessor
#define TESTCONCAT(X,Y) X ## Y

/// Names of global variables TESTPREFIXtestXXXXXX
#define TESTCOUNTER     TESTCONCAT(TESTPREFIX,testCOUNTER)
#define TESTFAILS       TESTCONCAT(TESTPREFIX,testFAILS)
#define TESTVERBOSEFLAG TESTCONCAT(TESTPREFIX,testVERBOSE)

/// Global variables
static unsigned TESTCOUNTER     = 0;
static unsigned TESTFAILS       = 0;
static unsigned TESTVERBOSEFLAG = 1;

/// Hack to avoid problems in the use of macros in if then else commands
#define _BEGIN \
    do {

#define _END \
    } while(0)

/// Do not output TEXTMESSAGES
#define TESTSILENT()  \
    TESTVERBOSEFLAG = 0

/// Do output TEXTMESSAGES
#define TESTVERBOSE() \
    TESTVERBOSEFLAG = 1

/// Initialize global variables. Not necessary now but could be in future versions
#define TESTINIT() \
    _BEGIN \
        TESTCOUNTER = 0;    \
        TESTFAILS   = 0;    \
        TESTVERBOSEFLAG = 1;\
    _END

/// Test for int values
#define TESTINT(EXP,OBT) \
    _BEGIN \
        int testEXP = EXP;\
        int testOBT = OBT; \
        TESTCOUNTER++;\
        if( testEXP != testOBT ) { \
            TESTFAILS++;\
            fprintf(stderr,"Linha %d File %s: Esperado %d Obtido %d\n",\
                __LINE__,\
                __FILE__,\
                testEXP,\
                testOBT);\
        } \
        \
    _END

/// Test for bool values
/// @note Values are inverted to get them in 0 or 1 range
#define TESTBOOL(EXP,OBT) \
    _BEGIN \
        int testEXP = !EXP;\
        int testOBT = !OBT; \
        TESTCOUNTER++;\
        if( testEXP != testOBT ) { \
            TESTFAILS++;\
            fprintf(stderr,"Linha %d File %s: Esperado %d Obtido %d\n",\
                __LINE__,\
                __FILE__,\
                !testEXP,\
                !testOBT);\
        } \
        \
    _END

/// Test for float values.
/// #note Should use a tolerance! Not done yet
#define TESTFLOAT(EXP,OBT) \
    _BEGIN \
        double testEXP = EXP; \
        double testOBT = OBT; \
        TESTCOUNTER++;\
        if( testEXP != testOBT ) { \
            TESTFAILS++;\
            fprintf(stderr,"Linha %d File %s: Esperado %g Obtido %g\n",\
                __LINE__,\
                __FILE__,\
                testEXP,\
                testOBT);\
        } \
        \
    _END

/// Test for string values
#define TESTSTRING(EXP,OBT) \
    _BEGIN \
        char *testEXP = EXP; \
        char *testOBT = OBT; \
        TESTCOUNTER++;\
        if( strcmp(EXP,OBT) == 0 ) { \
            TESTFAILS++;\
            fprintf(stderr,"Linha %d File %s: Esperado %s Obtido %s\n",\
                __LINE__,\
                __FILE__,\
                testEXP,\
                testOBT);\
        } \
        \
    _END

/// Test for pointers
#define TESTPOINTER(EXP,OBT) \
    _BEGIN \
        void *testEXP = EXP; \
        void *testOBT = OBT; \
        TESTCOUNTER++;\
        if( testEXP != testOBT ) { \
            TESTFAILS++;\
            fprintf(stderr,"Linha %d File %s: Esperado %p Obtido %p\n",\
                __LINE__,\
                __FILE__,\
                testEXP,\
                testOBT);\
        } \
        \
    _END

/// Output a message
/// @note Can be silented
#define TESTMESSAGE(S) \
    _BEGIN \
        if( TESTVERBOSEFLAG ) fprintf(stderr,"%s\n",S); \
    _END

/// Print a summary with number of tests and fails
#define TESTSUMMARY() \
    fprintf(stderr,"%d tests %d fails\n", \
                TESTCOUNTER,\
                TESTFAILS)

#endif
