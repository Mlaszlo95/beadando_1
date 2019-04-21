#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct team{
    char name[10];
    int name_long;
    int score;
};

typedef struct match{
    char first_team_n[10];
    char second_team_n[10];
    int first_t_result;
    int second_t_result;
};

typedef struct championship{
   char name[10];
   struct team team_in_champ[6];
   int t_count;
   struct match match_in_champ[60];
   int m_count;
};

/*2.csapat ujcsapat(char * c, int h), létrehoz egy csapatot, első param´etere
az azonos´ıt´ot tartalmaz´o karaktert¨omb kezd˝oc´ıme, m´asodik pedig a
benne l´ev˝o hasznos karakterek sz´ama.
*/

struct team new_team(char * c, int h){
    int i;
    struct team t;
    for(i = 0;i<h;i++){
        t.name[i] = c[i];
    }
    t.name_long = h;
    return t;
}
/*
    3. meccs ujmeccs(csapat cs1, csapat cs2, int x, int y) l´etrehozza a cs1 ´es
    cs2 k¨oz¨otti meccset x:y eredm´ennyel.
*/

struct match new_match(struct team cs1, struct team cs2, int x, int y){
    struct match new_match;

    strcpy(new_match.first_team_n,cs1.name);
    strcpy(new_match.second_team_n,cs2.name);
    new_match.first_t_result = x;
    new_match.second_t_result = y;

    return new_match;
}

/*
bajnoksag ujbajnoksag() l´etrehoz egy ´uj bajnoks´agot, melyben nulla
meccs van.
*/

struct championship new_champion_ship(){
    struct championship c;

    strcpy(c.name,"base");
    c.t_count = 0;
    c.m_count = 0;

    return c;
}

/*
    int meccs szam(bajnoksag b) visszaadja a bajnoks´agban eddig j´atszott
    meccsek sz´am´at.
*/

int number_of_match(struct championship c){
    return c.m_count;
}

int new_event(struct championship c,struct match m){
    int i;
    if(c.m_count>=60){
        return 1;
    }

    if(c.m_count==0){
       c.match_in_champ[0] = m;
       c.m_count++;
       return 0;
    }

    for(i = 0;i<c.m_count;i++){
        if((strcmp(c.match_in_champ[i].first_team_n,m.first_team_n) == 0) && (strcmp(c.match_in_champ[i].second_team_n,m.second_team_n) == 0)) return 1;
    }

    c.match_in_champ[c.m_count] = m;
    c.m_count++;

    return 0;
}


int missing_something(struct championship c){
    if(c.m_count == c.t_count * (c.t_count - 1)){
        return 0;
    }
    return 1;
}

void these_match_are_missing(struct championship c){
    int table_of_missing[2][6][6],helper = 0;
    int i,j,g,h;
    for(h = 0; h< 2; h++){
        for(i = 0; i<c.t_count;i++){
            for(j = 0;j<c.m_count;j++){
                if(strcmp(c.team_in_champ[i].name,c.match_in_champ[j].first_team_n)==0 && h==0){
                    g = 0;
                    while(g<c.t_count){
                        if(strcmp(c.match_in_champ[j].second_team_n,c.team_in_champ[g].name) == 0) break;
                        g++;
                    }

                    table_of_missing[h][i][g] = 1;
                }
                if(strcmp(c.team_in_champ[i].name,c.match_in_champ[j].second_team_n)==0 && h==1){
                    g = 0;
                    while(g<c.t_count){
                        if(strcmp(c.match_in_champ[j].first_team_n,c.team_in_champ[g].name) == 0) break;
                        g++;
                    }

                    table_of_missing[h][i][g] = 1;
                }
                if(table_of_missing[h][i][j] !=1) table_of_missing[h][i][j] = 0;
                if(i == j )table_of_missing[h][i][j] = 1;
            }
        }
    }
    for(h = 0; h< 2; h++){
        for(i = 0; i<c.t_count;i++){
            for(j = 0;j<c.m_count;j++){
                if(table_of_missing[h][i][j]==0) printf("%s - %s \n", c.team_in_champ[i].name,c.team_in_champ[j].name);
            }
        }
    }

}

int point(struct team t,struct championship c){
    int i,score = 0;
    for(i = 0;i<c.m_count;i++){
            if(strcmp(c.match_in_champ[i].first_team_n,t.name) == 0 || strcmp(c.match_in_champ[i].second_team_n,t.name) == 0){
                if(c.match_in_champ[i].first_t_result>c.match_in_champ[i].second_t_result) score = score + 3;
                if(c.match_in_champ[i].second_t_result>c.match_in_champ[i].first_t_result) score = score + 3;
                if(c.match_in_champ[i].first_t_result==c.match_in_champ[i].second_t_result) score = score + 1;
            }
    }
    return score;
}

int give_back_status(char status,struct championship c, struct team t){
    int i = 0, count = 0;
    switch(status){
        case 'o' :
            for(i; i<c.m_count;i++){
                if(c.match_in_champ[i].first_team_n == t.name || c.match_in_champ[i].second_team_n == t.name) count++;
            }
        ;
        break;
        case 'g' :
            for(i; i<c.m_count;i++){
                if(c.match_in_champ[i].first_team_n == t.name && c.match_in_champ[i].first_t_result > c.match_in_champ[i].second_t_result) count++;
                if(c.match_in_champ[i].second_team_n == t.name && c.match_in_champ[i].second_t_result > c.match_in_champ[i].first_t_result) count++;
            }
        ;
        break;
        case 'd' :
            for(i; i<c.m_count;i++){
                if(c.match_in_champ[i].first_team_n == t.name && c.match_in_champ[i].first_t_result == c.match_in_champ[i].second_t_result) count++;
                if(c.match_in_champ[i].second_team_n == t.name && c.match_in_champ[i].second_t_result == c.match_in_champ[i].first_t_result) count++;
            }
        ;
        break;
        case 'v' :
            for(i; i<c.m_count;i++){
                if(c.match_in_champ[i].first_team_n == t.name && c.match_in_champ[i].first_t_result < c.match_in_champ[i].second_t_result) count++;
                if(c.match_in_champ[i].second_team_n == t.name && c.match_in_champ[i].second_t_result < c.match_in_champ[i].first_t_result) count++;
            }
        ;
        break;
    }
    return count;
}

void tabela(struct championship c){
    int i;
    struct team helper;
    for(i = 0;i<c.t_count;i++){
        c.team_in_champ[i].score = point(c.team_in_champ[i],c);
    }
    i = 0;
     while(i<c.t_count-1) {
        if(c.team_in_champ[i].score>=c.team_in_champ[i+1].score){
            i++;
        }
        else {
            helper = c.team_in_champ[i+1];
            c.team_in_champ[i+1] = c.team_in_champ[i];
            c.team_in_champ[i] = helper;

            if(--i < 0) i = 0;
        }
    }


    for(i = 0; i<c.t_count;i++){
        if(i == 0){
            printf("%3s ","Hely");
            printf("%*s ",9,"nev");
            printf("%*s ",3,"o");
            printf("%*s ",5,"gy");
            printf("%*s ",3,"d");
            printf("%*s ",4,"v");
            printf("%*s ",4,"g arany");
            printf("%*s",5,"pont");
            printf("\n");
        }
        printf("%3d",i+1);
        printf("%*s",10,c.team_in_champ[i].name);
        printf("%*d",5,give_back_status('o',c,c.team_in_champ[i]));
        printf("%*d",5,give_back_status('g',c,c.team_in_champ[i]));
        printf("%*d",5,give_back_status('d',c,c.team_in_champ[i]));
        printf("%*d",5,give_back_status('v',c,c.team_in_champ[i]));
        printf("     - ");
        printf("%*d",5,c.team_in_champ[i].score);
        printf("\n");

    }
}

/*
typedef struct team{
    char name[10];
    int name_long;
    int score;
};

typedef struct match{
    char first_team_n[10];
    char second_team_n[10];
    int first_t_result;
    int second_t_result;
};

typedef struct championship{
   char name[10];
   struct team team_in_champ[6];
   int t_count;
   struct match match_in_champ[6*5];
   int m_count;
};
*/


int main(){
    struct championship new_c;
    strcpy(new_c.team_in_champ[0].name,"g");
    strcpy(new_c.team_in_champ[1].name,"a");
    strcpy(new_c.team_in_champ[2].name,"b");
    strcpy(new_c.team_in_champ[3].name,"c");
    strcpy(new_c.team_in_champ[4].name,"d");
    strcpy(new_c.team_in_champ[5].name,"e");
    new_c.t_count = 6;
    new_c.m_count = 3;

    strcpy(new_c.match_in_champ[0].first_team_n,"a");
    strcpy(new_c.match_in_champ[0].second_team_n,"b");
    new_c.match_in_champ[0].first_t_result = 3;
    new_c.match_in_champ[0].second_t_result = 4;

    strcpy(new_c.match_in_champ[1].first_team_n,"g");
    strcpy(new_c.match_in_champ[1].second_team_n,"a");
    new_c.match_in_champ[1].first_t_result = 4;
    new_c.match_in_champ[1].second_t_result = 4;

    strcpy(new_c.match_in_champ[2].first_team_n,"c");
    strcpy(new_c.match_in_champ[2].second_team_n,"d");
    new_c.match_in_champ[2].first_t_result = 1;
    new_c.match_in_champ[2].second_t_result = 3;

    tabela(new_c);
    these_match_are_missing(new_c);
    return 0;
}
