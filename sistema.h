// C program to detect Operating System
int detect()
{
#ifdef _WIN32
	return 0;       //0 se windows
#elif __linux__
    return 1;       //1 se linux 
#else
    return -1;      //sistema non supportato
#endif
}