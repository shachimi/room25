# include "utils/utils.hh"

char *itod(int allowed_dir)
{
    static char dir[5] = { 0 };
    int cpt = 0;

#define  ALLOWED_DIR(_dir)                                                   \
    if (allowed_dir & DIRECTION_##_dir) {                                    \
        dir[cpt++] = #_dir[0];                                               \
    }

    ALLOWED_DIR(N);
    ALLOWED_DIR(O);
    ALLOWED_DIR(S);
    ALLOWED_DIR(E);
#undef ALLOWED_DIR
    dir[cpt] = 0;
    return dir;
}

bool is_in_ref(char c, char *ref)
{
    int i = 0;

    while (ref[i]) {
        if (ref[i++] == c) {
            return true;
        }
    }
    return false;
}
