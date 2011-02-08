/**
 *  @file  Utils.h
 *  @brief Utilities file
 */
#ifndef _UTILS_H_
#define _UTILS_H_
#include <math.h>
#include <time.h>
/**
 * @class Utils
 * @brief A tools class
 */
class Utils
{
private:
    /**
     * Initialize the rand function
     */
    static int initialize(void);
    static int _count;
public:
    /**
    * Returns an int between min and max (inclusive)
    * @param min lower bound
    * @param max upper bound
    * @return An int between min and max (inclusive)
    */
	static int randRangeInt(int min, int max);
	/**
	 * Returns an unique int
	 * @return unique int
	 */
	static int unique(void);
};




#endif
