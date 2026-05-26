#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum scoreType_s { G, S } scoreType_t;

typedef enum grade_s
{
    GRADE_A_PLUS,
    GRADE_A,
    GRADE_A_MINUS,
    GRADE_B_PLUS,
    GRADE_B,
    GRADE_B_MINUS,
    GRADE_C_PLUS,
    GRADE_C,
    GRADE_C_MINUS,
    GRADE_F,
    GRADE_X
} grade_t;

typedef union score_s
{
    int score;
    grade_t grade;
} score_t;

typedef struct
{
    char id[16];
    int avg;
} student_t;

int gradeValue(grade_t g)
{
    switch (g)
    {
    case GRADE_A_PLUS:  return 95;
    case GRADE_A:       return 87;
    case GRADE_A_MINUS: return 82;
    case GRADE_B_PLUS:  return 78;
    case GRADE_B:       return 75;
    case GRADE_B_MINUS: return 70;
    case GRADE_C_PLUS:  return 68;
    case GRADE_C:       return 65;
    case GRADE_C_MINUS: return 60;
    case GRADE_F:       return 50;
    case GRADE_X:       return 0;
    default:            return 0;
    }
}

grade_t parseGrade(const char *s)
{
    if (strcmp(s, "A+") == 0) return GRADE_A_PLUS;
    if (strcmp(s, "A") == 0)  return GRADE_A;
    if (strcmp(s, "A-") == 0) return GRADE_A_MINUS;
    if (strcmp(s, "B+") == 0) return GRADE_B_PLUS;
    if (strcmp(s, "B") == 0)  return GRADE_B;
    if (strcmp(s, "B-") == 0) return GRADE_B_MINUS;
    if (strcmp(s, "C+") == 0) return GRADE_C_PLUS;
    if (strcmp(s, "C") == 0)  return GRADE_C;
    if (strcmp(s, "C-") == 0) return GRADE_C_MINUS;
    if (strcmp(s, "F") == 0)  return GRADE_F;
    return GRADE_X;
}

int percentToValue(int p)
{
    if (p == 0) return 0;
    if (p >= 90) return 95;
    if (p >= 85) return 87;
    if (p >= 80) return 82;
    if (p >= 77) return 78;
    if (p >= 73) return 75;
    if (p >= 70) return 70;
    if (p >= 67) return 68;
    if (p >= 63) return 65;
    if (p >= 60) return 60;
    return 50;
}

int scoreToValue(score_t sc, scoreType_t type)
{
    if (type == G)
        return gradeValue(sc.grade);
    return percentToValue(sc.score);
}

int studentCMP(const void *a, const void *b)
{
    const student_t *sa = (const student_t *)a;
    const student_t *sb = (const student_t *)b;
    if (sb->avg != sa->avg)
        return sb->avg - sa->avg;
    return strcmp(sa->id, sb->id);
}

int main(void)
{
    int n, m;
    scanf("%d %d", &n, &m);

    scoreType_t types[32];
    for (int i = 0; i < m; i++)
    {
        int t;
        scanf("%d", &t);
        types[i] = t ? S : G;
    }

    student_t students[128];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", students[i].id);
        int sum = 0;
        for (int j = 0; j < m; j++)
        {
            score_t sc;
            if (types[j] == G)
            {
                char buf[8];
                scanf("%s", buf);
                sc.grade = parseGrade(buf);
            }
            else
            {
                scanf("%d", &sc.score);
            }
            sum += scoreToValue(sc, types[j]);
        }
        students[i].avg = (sum + m / 2) / m;
    }

    qsort(students, n, sizeof(student_t), studentCMP);

    int top = n < 3 ? n : 3;
    for (int i = 0; i < top; i++)
        printf("%s - %d\n", students[i].id, students[i].avg);

    return 0;
}
