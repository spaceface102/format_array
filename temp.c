	//derefrence pointer correctly based on the specifier!
	//https://www.cplusplus.com/reference/cstdio/printf/ 
	switch(base_specifier[1]) //already check specifier[0] && strlen
	{
		case 'd': case 'i': 
			custom_print = print_int;
			break;
		case 'u': case 'o': case 'x': case 'X':
			custom_print = print_uint; //unsigned
			break;
		case 'c': case 's': 
			/*if 'c', specifier will ensure to print 
			only one char, and will throw out error if
			each index of the array is not a character 
			but character pointer
			if 's', specifier will ensure string are printed
			therefore user passed in an array of character 
			pointers, aka array of strings (think *argv[]) */
			custom_print = print_char;
			break;
		case 'f': //although will print as double, still have to derefrence correctly
			custom_print = print_float; 
			break;
		case 'F': //I will be treating this as double
			custom_print = print_double;
			break;
		case 'e': case 'E'://scientific notation
			if (type_size == 8) //double is 8 bytes
				custom_print = print_double;
			else if (type_size == 4) //float is 4 bytes
				custom_print = print_float;
			break;
		case 'p': //pointer address
			if (type_size == 8) //64 bit system
				custom_print = print_uint64;
			else if (type_size == 4) //32 bit system
				custom_print = print_uint32;
			else if (type_size == 2) //16 bit system
				custom_print = print_uint16;
			else if (type_size == 1) //8 bit system
				custom_print = print_uint8;
			break;	
		case 'h':
			if(base_spec_len >= 3) //either 3 or 4 
			{
				switch(base_specifier[2])
				{
					case 'd': case 'i':
						custom_print = print_short_int;
						break;
					case 'u': case 'o': case 'x': case 'X':
						custom_print = print_unsigned_short_int;
						break; 
					case 'h':	
						if(base_spec_len == 4)
						{
							switch(base_specifier[3])
							{
								case 'd': case 'i':
									custom_print = print_signed_char;
									break;
								case 'u': case 'o': case 'x': case 'X':
									custom_print = print_unsigned_char;
									break;
							}
						}
						break;
				}
			}
			break;
		case 'l':
			if(base_spec_len >= 3) //either 3 or 4
			{
				switch(base_specifier[2])
				{
					case 'f':
						custom_print = print_double;
						break;
					case 'd': case 'i':
						custom_print = print_long_int;
						break;
					case 'u': case 'o': case 'x': case 'X':
						custom_print = print_unsigned_long_int;
						break;
					case 'l':
						if (base_spec_len == 4)
						{
							switch(base_specifier[3])
							{
								case 'd': case 'i':
									custom_print = print_long_long_int;
									break;
								case 'u': case 'o': case 'x': case 'X':
									custom_print = print_unsigned_long_long_int;
									break;
							}
						}
						break;
				}
			}
			else //base_spec_len == 2
				custom_print = print_long_int;
			break;
		default:
			printf("Unknown specifier: %s\n", specifier);
			return;
	}
	//------------------------------------------------------------------------
