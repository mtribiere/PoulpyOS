#pragma once

unsigned char read_port_byte (unsigned short port);
void write_port_byte(unsigned short port, unsigned char data);
unsigned short read_port_word (unsigned short port);
void write_port_word(unsigned short port, unsigned short data);
