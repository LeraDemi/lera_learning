#ifndef _INTEGER_H
#define _INTEGER_H


/*************************************
 * INCLUDES
 *************************************/

#include <stdint.h>
#include <stdlib.h>


/*************************************
 * TYPES
 *************************************/
typedef enum
{
	FAIL,
	SUCCESS
}STATUS;

typedef struct
{
	uint64_t* val;
}INT;
/*************************************
 * FUNCTIONS
 *************************************/
 /**
 * @brief Function gets a pointer to integer and increases its value by 1
 *
 * @param integer - pointer to integer to be increased
 *
 * @return returns SUCCESS if operation was successfull and FAIL if an error accured
 */
 STATUS inc(INT* integer);
  /**
 * @brief Function gets a pointer to integer and decreases its value by 1
 *
 * @param integer - pointer to integer to be decreased
 *
 * @return returns SUCCESS if operation was successfull and FAIL if an error accured
 */
 STATUS dec (INT* integer);
   /**
 * @brief Function gets a pinter to integer and zeroizes its value (makes it zero)
 *
 * @param integer - pointer to integer to be zeroized
 *
 * @return returns SUCCESS if operation was successfull and FAIL if an error accured
 */
 STATUS zero(INT* integer);
   /**
 * @brief Function gets a pinter to integer and prints its value
 *
 * @param integer - pointer to integer to be printed
 *
 * @return void
 */
 void ptint(INT* integer);

#endif
