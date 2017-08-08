/**
 * Copyright (c) 2013-2017 Husarion Sp. z o.o.
 * Distributed under the MIT license.
 * For full terms see the file LICENSE.md.
 */

#ifndef __HSYSTEM_H__
#define __HSYSTEM_H__

#include <functional>

#include <hTypes.h>
#include <hPrintfDev.h>
#include <thread>

namespace hFramework
{
class hTask {
	friend class hSystem;

	bool running = true;
	std::thread thread;
	hTask() {}
public:
	void join();
	bool isRunning() { return running; }
};

constexpr int DEFAULT_STACK_SIZE = 0; // stack size is ignored on Linux

class hSystem
{
	hSystem(const hSystem&) = delete;
	static uint64_t startTime;

public:
	hSystem(); //!< Initialize system object.

	/**
	 * @brief Create a new task.
	 * @param taskProc an TaskProcUserData argument
	 * @param param a void pointer to the object with parameters
	 * @param priority a priority of the task (the higher the number, the higher priority)
	 * @param stack a size of table dynamically allocated as stack for current task (single element of this table is uint32_t)
	 * @param desc a C-string with task description used in debugging
	 * @return the created task handle
	 */
	static hTask& taskCreate(const std::function<void()>& handler, uint8_t priority = 2, uint32_t stack = DEFAULT_STACK_SIZE, const char* desc = 0);

	static hTask& taskCreate(const std::function<void()>& handler, const char* desc) {
        return taskCreate(handler, 2, DEFAULT_STACK_SIZE, desc);
    }

	/**
	 * @brief Get timestamp from all time working timer with 1us resolution
	 * @return timer counter value is [us]
	 */
	static uint32_t getUsTimVal();

	/**
	 * @brief Delay the current task.
	 * @param delay milliseconds to delay
	 */
	static void delay(uint32_t delayMs);

	/**
	 * @brief Delay the current task.
	 * @param delay microseconds to delay (must be multiply of 500)
	 */
	static void delayUs(uint32_t delay);

	/**
	 * @brief Get system time.
	 * @return system time in ms
	 */
	static unsigned long getRefTime();

	/**
	 * @brief Get the random number generated by hardware random number generator.
	 * @return generated random number
	 */
	static uint32_t getRandNr();

	/**
	 * @brief Get the random number generated by hardware random number generator.
	 * @return generated random number
	 */
	static uint64_t getSerialNum();

	/**
	 * @brief Dynamicaly allocate memory on the heap.
	 * @param size number of bytes to be dynamically allocated
	 * @return pointer to dynamically allocated memory
	 */
	static void* malloc(uint32_t size);

	/**
	 * @brief Free allocated memory.
	 * @param ptr pointer to dynamically allocated memory
	 */
	static void free(void * ptr);
};

extern hSystem sys;

}

#endif /* __HSYSTEM_H__ */
