#ifndef RWE_COBTHREAD_H
#define RWE_COBTHREAD_H

#include <rwe/cob/CobFunction.h>
#include <rwe/util.h>
#include <stack>
#include <variant>
#include <vector>

namespace rwe
{
    class CobThread
    {
    public:
        std::string name;

        std::stack<int> stack;

        unsigned int signalMask{0};

        std::stack<CobFunction> callStack;

        int returnValue;

        /**
         * Required for query functions, which communicate back to the engine
         * not by a return value but by changing the values of their input parameters.
         */
        std::vector<int> returnLocals;

    public:
        CobThread(const std::string& name, unsigned int signalMask);

        explicit CobThread(const std::string& name);
    };
}

#endif
