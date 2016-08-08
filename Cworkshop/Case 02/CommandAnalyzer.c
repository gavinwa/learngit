#define CHAR_SPACE ' '
#define CHAR_QUOTE '\"'
#define CHAR_NULL '\0'

#include <stdio.h>
#include <stdlib.h>

enum Status
{
	Begin,
	KeywordStart,
	KeywordEnd,
	ParaStart,
	ParaEnd,
	OneQuoteFound,
	InsideQuoteParaStart,
	InsideQuoteParaEnd,
	ErrorEngaged,
	End,
};

int AnalyzeCmd(char* cmd, char* szCmdName, char** argv)
{
	char *pcmd = cmd;			// point to input string.
	char *pCmdName = szCmdName; // point to command name.
	char **pargv = argv;		// point to parameter array.
	char *ppara = *pargv;		// point to each parameter.	
	int nParCount = 0;			// The amount of parameter.
	enum Status curStatus = Begin;

	do
	{
		switch(curStatus)
		{
		case (Begin):
			switch(*pcmd)
			{
			case (CHAR_SPACE):
				break;
			case (CHAR_QUOTE):
				curStatus = ErrorEngaged;
				break;
			case (CHAR_NULL):
				curStatus = ErrorEngaged;
				break;
			default: // Common characters.
				curStatus = KeywordStart;
				*pCmdName = *pcmd;
				pCmdName++;
			}
			break;
			
		case (KeywordStart): 
			switch(*pcmd)
			{
			case (CHAR_SPACE):
				*pCmdName = '\0';
				curStatus = KeywordEnd;
				break;
			case (CHAR_QUOTE):
				curStatus = ErrorEngaged;
				break;
			case (CHAR_NULL):
				*pCmdName = '\0';
				curStatus = End;
				break;
			default: // Common characters.
				*pCmdName = *pcmd;
				pCmdName++;
			}
			break;

		case  (KeywordEnd):
			switch(*pcmd)
			{
			case (CHAR_SPACE):
				break;
			case (CHAR_QUOTE):
				curStatus = OneQuoteFound;
				break;
			case (CHAR_NULL):
				curStatus = End;
				break;
			default: // Common characters.
				curStatus = ParaStart;
				*ppara = *pcmd;
				ppara++;
			}
			break;

			case (ParaStart): 
				switch(*pcmd)
				{
				case (CHAR_SPACE):
					*ppara = '\0';
					pargv++;
					ppara = *pargv;
					nParCount++;
					curStatus = ParaEnd;
					break;
				case (CHAR_QUOTE):
					curStatus = ErrorEngaged;
					break;
				case (CHAR_NULL):
					*ppara = '\0';
					nParCount++;
					curStatus = End;
					break;
				default: // Common characters.
					*ppara = *pcmd;
					ppara++;
					break;
				};
				break;

			case (ParaEnd):
				switch(*pcmd)
				{
				case (CHAR_SPACE):
					break;
				case (CHAR_QUOTE):
					curStatus = OneQuoteFound;
					break;
				case (CHAR_NULL):
					curStatus = End;
					break;
				default: // Common characters.
					curStatus = ParaStart;
					*ppara = *pcmd;
					ppara++;
					break;
				};
				break;

			case (OneQuoteFound): 
				switch(*pcmd)
				{
				case (CHAR_SPACE):
					curStatus = InsideQuoteParaStart;
					*ppara = *pcmd;
					ppara++;
					break;
				case (CHAR_QUOTE):
					curStatus = ErrorEngaged;
					break;
				case (CHAR_NULL):
					curStatus = ErrorEngaged;
					break;
				default: // Common characters.
					curStatus = InsideQuoteParaStart;
					*ppara = *pcmd;
					ppara++;
					break;
				};
				break;

			case(InsideQuoteParaStart) : 
				switch(*pcmd)
				{
				case (CHAR_SPACE):
					*ppara = *pcmd;
					ppara++;
					break;
				case (CHAR_QUOTE):
					curStatus = InsideQuoteParaEnd;
					break;
				case (CHAR_NULL):
					curStatus = ErrorEngaged;
					break;
				default: // Common characters.
					*ppara = *pcmd;
					ppara++;
					break;
				};
				break;

			case (InsideQuoteParaEnd): 
				switch(*pcmd)
				{
				case (CHAR_SPACE):
					*ppara = '\0';
					pargv++;
					ppara = *pargv;
					nParCount++;
					curStatus = ParaEnd;
					break;
				case (CHAR_QUOTE):
					curStatus = ErrorEngaged;
					break;
				case (CHAR_NULL):
					*ppara = '\0';
					nParCount++;
					curStatus = End;
					break;
				default: // Common characters.
					curStatus = ErrorEngaged;
					break;
				};
				break;
				
			default:
				break;
		}
	} while ('\0' != *(pcmd++) && ErrorEngaged != curStatus);
	
	// Make a judgement that normal quit or error.
	if (ErrorEngaged == curStatus)
	{
		nParCount = -1;
	}

	// Return the result.
	return nParCount;
}


void main()
{
	char* cmdline = "  cmdLine para1 \"  para 2\" \"para 3  \"   \"  para4  \"  ";
	char cmdName[32];
	char** argv;
	int parCount;
	int i;

	// Initialize memory.
	argv = (char**)malloc(sizeof(char*) * 32);
	for(i=0; i<32; i++)
	{
		*(argv+i) = (char*)malloc(sizeof(char) * 32);
	}
	
	// Perform analyze.
	parCount = AnalyzeCmd(cmdline, cmdName, argv);
	
	// Output.
	if (-1 != parCount)
	{
		printf("command: \"%s\"\n", cmdName);
		printf("number of arguments:%d\n", parCount);
		printf("arguments values:\n");
		for(i=0; i<parCount; i++)
		{
			printf("    \"%s\"\n", argv[i]);
		}
	}
	else
	{
		printf("Bad format.\n");
	}

	// Release memory.
	for(i=0; i<32; i++)
	{
		free(argv[i]);
	}
}
