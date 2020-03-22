#ifndef CHECKSUM_H_
#define CHECKSUM_H_

/*
 * checksum.h
 *
 * Created: 7/30/2016 3:25:41 PM
 *  Author: ASUS
 */ 

#include "common.h"


// Must Give even number of data points.
uint16_t checksum(char data[],uint16_t start_pos, uint16_t end_pos);

#endif /* CHECKSUM_H_ */
