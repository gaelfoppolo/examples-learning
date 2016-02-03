/**
 *
 * @gaelfoppolo FOPPOLO Gaël
 * @Ebatsin PHILIP Bastien
 *
 * @brief The core
 */

#include "core.h"

int nbCombi(Examples* exp, int step) {
    // init with 1, neutral of multiplication
    int nbCombi = 1;
    for (int i = step; i < vectSize(exp->examples); ++i) {
        nbCombi *= vectSize(vectAt(exp->examples, i).objects);
    }
    return nbCombi;
}

OutObject* initOutObjectWithObject(Model* mdl, Object* o) {
    OutObject* oo = (OutObject*)malloc(sizeof(OutObject));
    initOutObject(oo);
    OutAttribute* oa = (OutAttribute*)malloc(sizeof(OutAttribute));
    Attribute att;

    for(int i = 0; i < vectSize(o->attributes); ++i) {
        att = vectAt(o->attributes, i);
        oa->type = att.type;

        switch(att.type) {
            case TYPE_INT:
                oa->inter.min = att.value;
                oa->inter.max = att.value;
                break;
            case TYPE_ENUM:
                initOutEnum(&oa->oenu);
                vectPush(int, oa->oenu.oenu, att.value);
                break;
            case TYPE_TREE:
                oa->tree = att.value;
                break;
        }
        vectPush(OutAttribute, oo->attributes, *oa);
        
    }
    for (int j = 0; j < vectSize(mdl->rel); ++j) {
            vectPush(OutObject*, oo->relations, (OutObject*)NULL);
    }
    return oo;
}

Solution* initAllCombi(Model* mdl, Examples* exp) {
    int allCombi = nbCombi(exp, 0);
    Solution* T = (Solution*)malloc(sizeof(Solution));
    initSolution(T);
    Example lastExample = vectAt(exp->examples, vectSize(exp->examples)-1);
    int sizeLastExample = vectSize(lastExample.objects);
    
    Object* o;
    OutObject* oo;

    while(vectSize(T->outobjects) < allCombi) {

        for (int i = 0; i < sizeLastExample; ++i) {
            // get the adress of the i object in the last exemple
            o = &vectAt(lastExample.objects, i);
            oo = initOutObjectWithObject(mdl, o);
            vectPush(OutObject, T->outobjects, *oo);
        }
    }
    return T;

}

void combiOutObjectObject(Model* mdl, OutObject* oo, Object*o) {
    OutAttribute* oa = (OutAttribute*)malloc(sizeof(OutAttribute));
    Attribute att;
    int pt;

    for(int i = 0; i < vectSize(o->attributes); ++i) {
        att = vectAt(o->attributes, i);
        oa = &vectAt(oo->attributes, i);

        switch(att.type) {
            case TYPE_INT:
                addToInterval(&oa->inter, att.value);
                break;
            case TYPE_ENUM:
                vectIndexOf(oa->oenu.oenu, att.value, pt);
                if (pt == -1) vectPush(int, oa->oenu.oenu, att.value);
                break;
            case TYPE_TREE:
                // looking for tree model (root) in the model (same rank), then LCA
                oa->tree = LCA(&vectAt(mdl->ma, i).mt.tree, oa->tree, att.value)->id;
                break;
        }        
    }

}

Solution* genAllCombi(Model* mdl, Examples* exp) {
    Solution* T = initAllCombi(mdl, exp);
    int fact, factNext, nbExamples = vectSize(exp->examples), nbAllCombi = nbCombi(exp, 0);
    Example e;
    // begin from last last examples to first one
    for (int step = nbExamples-2; step >= 0; --step) {
        e = vectAt(exp->examples, step);
        fact = nbCombi(exp, step+1);
        factNext = nbCombi(exp, step);

        for (int i = 0; i < nbAllCombi/factNext; ++i) {
            
            // for all the object of that example
            for (int j = 0; j < vectSize(e.objects); ++j) {

                for (int k = 0; k < fact; ++k) {
                    
                    // combi the OutObject with the current Object
                    combiOutObjectObject(mdl, &vectAt(T->outobjects, i*factNext+j*fact+k), &vectAt(e.objects, j));
                }
            }            
        }
    }
    return T;
}

int getIndex(Examples* exp, ObjectIndice* oi) {
    int index = 0, inside, i;
    for (i = 0; i < vectSize(exp->examples)-2; ++i) {
        inside = 1;
        for (int j = i+1; j < vectSize(exp->examples)-1; ++j) {
            inside *= vectSize(vectAt(exp->examples, j).objects);
        }
        index += vectAt(oi->indices, i)*inside;
    }
    return index+vectAt(oi->indices, i);
}