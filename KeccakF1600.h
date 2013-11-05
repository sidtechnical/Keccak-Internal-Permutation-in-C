/* Implement the following API.
 * You can add your own functions, but don't modify below this line.
 */

unsigned long** KeccakF(unsigned long** INPUT);
/*Function Definations */
unsigned long** rounds(unsigned long**,unsigned long);
unsigned long** theta_step(unsigned long**);
unsigned long** pi_step(unsigned long**);
unsigned long** x_step(unsigned long** ,unsigned long**);
unsigned long rot(unsigned long, unsigned int);


