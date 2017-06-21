/*
 * ================================
 * eli960@qq.com
 * http://www.mailhonor.com/
 * 2017-01-06
 * ================================
 */

#include "zcc.h"

void ___usage(char *arg)
{
    printf("USAGE: %s -f filename1 [filename2 ...]\n", zcc::var_progname);
    exit(1);
}

void dorun(const char *fn)
{
    char charset[64];
    std::string content;

    zcc::file_get_contents_sample(fn, content);

    if (zcc::charset_detect_cjk(content.c_str(), content.size(), charset) < 0) {
        printf("%-30s: not found, maybe ASCII\n", fn);
    } else {
        printf("%-30s: %s\n", fn, charset);
    }
}

int main(int argc, char **argv)
{
    std::vector<char *> fn_vec;
    zcc::var_progname = argv[0];

    if (argc < 2) {
        ___usage(0);
    }
    zcc_main_parameter_begin() {
        if (optval == 0) {
            ___usage(0);
        }
        if (!strcmp(optname, "-f")) {
            if (optval_count < 1) {
                ___usage(optname);
            }
            int i;
            for (i=0;i<optval_count;i++) {
                fn_vec.push_back(argv[opti + 1 + i]);
            }
            opti += 1 + optval_count;
            continue;
        }
    } zcc_main_parameter_end;


    std::vector<char *>::iterator fit;
    for (fit = fn_vec.begin(); fit != fn_vec.end(); fit++) {
        dorun(*fit);
    }

    return 0;
}
