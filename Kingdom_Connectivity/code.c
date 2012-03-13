#include <stdio.h>
#include <malloc.h>

#define CITY(num) (num-1)

/* 记录 结果*/
char roadnum = 0;

typedef struct tnode* Tptr;
typedef struct tnode {
    int cnum;
    Tptr next;
} Treenode;

int citys,roads;
int getResult( int cnum, int cfrom, Tptr* arr, int **cstus);

int main() {
    scanf("%d %d",&citys,&roads);

    /* 记录道路的起止点 */
    Tptr* roadto;
    /* 记录每个城市的道路导入数*/
    int *citystus;

    Tptr** cityptr;

    roadto = (Tptr*)calloc( citys , sizeof( Tptr ) );
    citystus = (int*)calloc( citys , sizeof( int ) );
    cityptr = (Tptr**)calloc( citys , sizeof( Tptr* ) );

    *citystus = 1;
	
    if( roadto == NULL ) {
        printf("out of menory,press any key to....");
        exit(0);
    }

    int i,j;

    //初始化
/*
    for( i =0;i<citys;i++) {

        roadto[i] = (char*)calloc( citys, sizeof( char ) );
    }
*/

    int line;
    int cf,ct;

    for( line = 0; line < roads; line ++ ) {

        scanf("%d %d",&cf,&ct);   
        cf = CITY(cf);
        ct = CITY(ct);

        Tptr cr = (Tptr)malloc( sizeof(Treenode));
        cr->cnum = ct;
        cr->next = NULL;

        if( (cityptr[ cf ]) == NULL  ) {

            roadto[ cf ] = cr;
            (cityptr[ cf ]) = &(roadto[ cf ]);
        } else {

            (*cityptr[ cf ])->next = cr;
            (cityptr[ cf ]) = &((*cityptr[ cf ])->next);
        }
 //       *(*(roadto+cf ) + ct) = 1;
    }

    getResult(0, 0, roadto, &citystus );
/*
    for( j=0;j<citys;j++) {

		Tptr out = roadto[j];
        while( out ) {
            printf("%d_ ",out->cnum );
            out = out->next;
        }

        printf("\n");
    }
    printf("\n");
*/
    printf("%d",roadnum );

}


int getResult( int cnum , int cfrom, Tptr* arr ,int **cstus ) {
    int i;
    char hasnext = 0;
    /* 将此点属性等同于 前一点 */
    *(*cstus + cnum) = *(*cstus + cfrom);
 
 	Tptr tcity = arr[ cnum ];
    while( tcity != NULL ) {
    	
    	i = tcity->cnum;
    	
    	tcity = tcity->next;
    	
        hasnext = 1;

        if( i == CITY(citys) ) {

            char nstatus = *( *cstus + cnum);

            if( nstatus == 1 ) {
                roadnum ++;
                //( *( *cstus + i) ) ++;
                //*( *cstus + cnum) = 0;
                //return 1;
            }
            
            if( nstatus == 2 ) {
                printf("INFINITE PATHS");
                exit(0);
            }
        }      

        /*当节点不为零时，说明产生回路 */
        int nc = *(*cstus+i);

        if( nc == 0 ) {
             int res = getResult( i,cnum, arr, cstus);

             if( cnum == 0 ) {
                continue;
             }

             if ( (*(*cstus+cnum)) != 2 ) {
             	(*(*cstus+cnum)) = res;
             }
        } else {

            if( *(*cstus+ CITY(citys) ) == 1 ) {
                
                printf("INFINITE PATHS");
                exit(0);
            }

            (*(*cstus+i)) = 2;
            (*(*cstus+cnum)) = 2;
            continue;
        }
    }
    
    if( hasnext == 0 ) {
        (*(*cstus+cnum)) = 0;
        return 1;
    }

    int rt = (*(*cstus+cnum));

    (*(*cstus+cnum)) = 0;

    return rt;
       
}