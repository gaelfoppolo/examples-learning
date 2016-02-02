#include "output.h"

void genOutput(Solution* sol, Model* mdl) {
    // out final string to display

    ModelAttribute ma;
    OutObject oo;
    OutAttribute oa;

    for(int i = 0; i < vectSize(sol->outobjects); ++i) {
        
        // get current OutObject
        oo = vectAt(sol->outobjects, i);

        for (int j = 0; j < vectSize(oo.attributes); ++j) {
            // get current model attribute data
            ma = vectAt(mdl->ma, j);
            oa = vectAt(oo.attributes, j);

            // add attribute name
            printf("%s(", ma.name);

            switch (ma.mt.type) {
                case TYPE_INT:
                    // get interval value as char*
                    printf("%d-%d", oa.inter.min, oa.inter.max);
                    break;
                case TYPE_ENUM:
                    for (int k = 0; k < vectSize(oa.oenu.oenu); ++k) {
                        printf("%s", getEnumStr(vectAt(oa.oenu.oenu, k), mdl, j));
                        if (k+1 < vectSize(oa.oenu.oenu)) printf(", ");
                    }
                    break;
                case TYPE_TREE:
                    printf("%s", getTreeStr(oa.tree, mdl, j));
                    break;
            }
            printf(")");
            if (j+1 < vectSize(oo.attributes)) printf(", ");
        }
        printf("\n");
    }
}

char* cPrint(const char * fmt, ...) {
	va_list args;
    va_start(args, fmt); // inits the valist

	unsigned long sz = vsnprintf(NULL, 0, fmt, args) + 1; // get the size of the formatted output but does not write it yet
	char* c = (char*)malloc(sizeof(char) * sz);

	va_end(args); // refresh the valist
	va_start(args, fmt);
	vsnprintf(c, sz, fmt, args); // write the formatted output in a string with the right length calculated before

	va_end(args);
	return c;
}
