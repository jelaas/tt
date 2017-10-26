#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char *names[] = {
	"ACUTE", "´",
	"AMPERSAND", "&",
	"AND", "&&",
	"APPEND", ">>",
	"APOSTROPHE", "'",
	"ASTERISK", "*",
	"ATSIGN", "@",
	"BACKSLASH", "\\",
	"CIRCUMFLEX", "^",
	"COLON", ":",
	"COMMA", ",",
	"DASH", "-",
	"DOLLAR", "$",
	"PERIOD", ".",
	"EQUALS", "=",
	"ESCAPE", "\\",
	"EXCLAMATIONMARK", "!",
	"GT", ">",
	"GRAVE", "`",
	"GREATERTHAN", ">",
	"HASH", "#",
	"LEFTCURLYBRACKET", "{",
	"LEFTPARENTHESIS", "(",
	"LEFTSQUAREBRACKET", "[",
	"LESSTHAN", "<",
	"LBRACK", "[",
	"LCURLY", "{",
	"LPAR", "(",
	"LT", "<",
	"MINUS", "-",
	"OR", "||",
	"PERCENT", "%",
	"PIPE", "|",
	"PLUS", "+",
	"QUESTIONMARK", "?",
	"QUOTATIONMARK", "\"",
	"QUOTE", "\"",
	"RBRACK", "]",
	"RCURLY", "}",
	"RIGHTCURLYBRACKET", "}",
	"RIGHTPARENTHESIS", ")",
	"RIGHTSQUAREBRACKET", "]",
	"ROOF", "^",
	"RPAR", ")",
	"SEMICOLON", ";",
	"SLASH", "/",
	"SPACE", " ", "SPC", " ",
	"STAR", "*",
	"TAB", "\t",
	"TILDE", "~",
	"UNDERSCORE", "_",
	(void*)0, (void*)0
};

int main(int argc, char **oargv, char **envp)
{
	char *argv[4];
	char *cmd, *p;
	int i, j, len=1;
	int verb = 0;

	if(argc == 2 && !strcmp(oargv[1], "EXAMPLES")) {
		printf("'ls -l /etc' => 'tt ls SPC DASH l SPC SLASH etc'\n");
		exit(0);
	}
	if(argc == 1 || (argc == 2 && !strcmp(oargv[1], "HELP"))) {
		printf(
			"tt executes its arguments under 'bash -c' after performing translations of words into characters or character combinations.\n"
			"Use 'tt HELP' to display translations performed.\n\n"
			"HELP 1|<N>\n"
			"EXAMPLES\n"
			"VERB|VERBATIM \tSkip translation of next word.\n"
			);
		exit(0);
	}
	if(argc == 3 && !strcmp(oargv[1], "HELP")) {
		int n;
		n = atoi(oargv[2]);
		if(n) n--;
		for(j=0;j<(n+1)*20;j+=2) {
			if(!names[j]) break;
			if(j<n*20) continue;
			printf("%-20s '%s'\n", names[j], names[j+1]);
		}
		exit(0);
	}
	
	for(i=1;i<argc;i++) {
		len += strlen(oargv[i]);
		len++;
	}
	
	cmd = malloc(len);

	for(p=cmd, i=1;i<argc;i++) {
		if(verb) { verb = 0; p += sprintf(p, "%s", oargv[i]); continue; }
		if(!strcmp(oargv[i], "VERBATIM")) { verb = 1; continue; }
		if(!strcmp(oargv[i], "VERB")) { verb = 1; continue; }
		for(j=0;;j+=2) {
			if(!names[j]) break;
			if(!strcmp(oargv[i], names[j])) {
				p += sprintf(p, names[j+1]);
				goto next;
			}
		}
		p += sprintf(p, "%s", oargv[i]);
	next:
		continue;
	}	
	
	argv[0] = "/bin/bash";
	argv[1] = "-c";
	argv[2] = cmd;
	argv[3] = (void*)0;
	
	execve("/bin/bash", argv, envp);
	exit(2);
}
