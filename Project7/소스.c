#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct {
	char name[14]; //과목명 및 교수명
	int time[3]; //시간
} information;

int strcmp(char str1[], char str2[]);
void strcpy(char str1[], char str2[]);
void timetable_input(char timetable[][14], information subject[], int i);
void timetable_print(char timetable[][14], int timetable_number, int ge_credit, int other_time, char other_name[], int kw);
void timetable_delete(char timetable[][14], information subject[], int i);
void timetable_made(char timetable[][14], information* subject[], int group_number, int subject_number[], int day_num, int lec, int lectures[], int* timetable_number, int ge_credits[], int kw);
void class_pick(char timetable[][14], char cls[]);
void kwangwoon(char timetable[][14], int* kw, int lectures[]);
void science_pick(information subject[], int* science);
void ge_pick(information subject[], int* ge, int ge_credits[], int lec, int day_num);
void day_off(int science, int* day_num, int kw);
void lectures_4(int* lec);


int main(void) {
	char timetable[30][14] = { " ", }; //시간표
	for (int i = 0; i < 30; i++) {
		strcpy(timetable[i], "             ");
	}

	char cls[3] = " "; // 분반 선택용 변수
	int kw = 0; // 광운인되기 or 소프트웨어입문세미나 확인용 변수
	char yn[7] = " "; // 네 아니오 선택용 변수
	int n = 0;// 숫자 선택용 변수
	int science = 0; // 물리 or 화학 선택 확인용 변수
	int ge = 0; // 선택한 균형교양 수 확인용 변수
	int ge_credits[6] = { 0, 0, 0, 0, 0, 0 }; // 균형교양의 학점 확인용 변수
	int day_num = 99; // 공강 날짜 선택용 변수
	int lec = 0; // 하루에 4개 이상의 강의 포함  동의 여부
	int lectures[5] = { 0, 0, 0, 0, 0 };// 하루에 4개이상의 강의가 포함되었는지 확인
	int timetable_number = 0; // 출력된 시간표의 수

	information subject1[6] = {
		{ "대수 1 류송분", { 5, 2, 37 } }, { "대수 1 백혜숙", { 15, 12, 37 } }, { "대수 1 박정준", { 25, 22, 37 } }, { "대수 1 박주희", { 1, 8, 37 } }, { "대수 1 박지연", { 4, 9, 37 } }, { "대수 1 연윤정", { 24, 29, 37 } }
	};

	information subject2[9] = {
		{ "융사글 박상현", { 0, 7, 37 } }, { "융사글 전도현", { 5, 2, 37 } }, { "융사글 정재훈", { 20, 27, 37 } }, { "융사글 전지은", { 25, 22, 37 } }, { "융사글 신정은", { 6, 3, 37 } }, { "융사글 이소망", { 16, 13, 37 } }, { "융사글 김학현", { 21, 28, 37 } }, { "융사글 박보름", { 4, 9, 37 } }, { "융사글 손병현", { 14, 19, 37 } }
	};

	information subject3[3]; // 기초과학

	information subject4[6]; // 균형교양

	information* subject[4] = { subject1, subject2, subject3, subject4 };

	//공설입은 분반이 하나이기 때문에 바로 입력
	strcpy(timetable[10], "공설입 임재한");
	strcpy(timetable[17], "공설입 임재한");

	//C프와 공설입은 무조건 월, 수에 포함되어있음
	lectures[0] += 2;
	lectures[2] += 2;

	printf("1학년 1학기 소프트웨어학부 시간표 생성 프로그램입니다.\n");
	printf("\n2학기에도 팀프로젝트 과목이 있기 때문에 부담을 줄이고자 공학설계입문이 이번 시간표에 들어가게 됩니다.\n ");

	class_pick(timetable, cls);
	printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	kwangwoon(timetable, &kw, lectures);
	printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	science_pick(subject3, &science);
	printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	day_off(science, &day_num, kw);
	printf("\n--------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	lectures_4(&lec);
	printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	ge_pick(subject4, &ge, ge_credits, lec, day_num);
	printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	printf("\n지금까지 고른 목록입니다.\n");

	printf("\n분반 : %s\n", cls);

	if (kw == 1)
		printf("\n광운인되기 or 소프트웨어입문세미나 : 광운인되기\n");
	else
		printf("\n광운인되기 or 소프트웨어입문세미나 : 소프트웨어입문세미나\n");

	if (science == 3)
		printf("\n기초과학 : 대학물리학1\n");
	else
		printf("\n기초과학 : 대학화학및실험1\n");

	printf("\n교양 :\n\n");
	int k = 1; //번호 출력용 변수
	for (int i = 0; i < ge; i++) {
		if (i > 0 && strcmp(subject4[i].name, subject4[i - 1].name))
			continue;
		printf("%d. %s   ", k, subject4[i].name);
		k++;
	}

	if (day_num == 99)
		printf("\n\n공강인 요일 : 없음\n");
	else if (day_num == 1)
		printf("\n\n공강인 요일 : 화\n");
	else if (day_num == 3)
		printf("\n\n공강인 요일 : 목\n");
	else if (day_num == 4)
		printf("\n\n공강인 요일 : 금\n");

	if (lec == 0)
		printf("\n하루에 4개 이상의 강의 : 있음\n");
	else
		printf("\n하루에 4개 이상의 강의 : 없음\n");

	printf("\n다시 고르고 싶은 것이 있나요? ( 네 or 아니오 ) : ");
	getchar();
	while (1) {
		scanf("%s", yn);
		if (strcmp(yn, "네")) {
			printf("\n다시 선택할 것을 골라 주세요.\n\n1. 분반   2. 광운인되기 or 소프트웨어입문세미나   3. 기초 과학   4. 교양   5. 공강 여부   6. 하루 4개 이상의 강의 여부\n\n( 숫자로 입력 ) : ");
			getchar();
			while (1) {
				scanf("%d", &n);
				if (n == 1) {
					if (strcmp(cls, "c4") || strcmp(cls, "C4")) {
						strcpy(timetable[15], "             ");
						strcpy(timetable[12], "             ");
					}
					else if (strcmp(cls, "c5") || strcmp(cls, "C5")) {
						strcpy(timetable[20], "             ");
						strcpy(timetable[27], "             ");
					}
					else {
						strcpy(timetable[25], "             ");
						strcpy(timetable[22], "             ");
					}
					class_pick(timetable, cls);
				}
				else if (n == 2) {
					kwangwoon(timetable, &kw, lectures);
				}
				else if (n == 3) {
					science_pick(subject3, &science);
				}
				else if (n == 4) {
					ge = 0;
					ge_pick(subject4, &ge, ge_credits, lec, day_num);
				}
				else if (n == 5) {
					day_off(science, &day_num, kw);
				}
				else if (n == 6) {
					lectures_4(&lec);
				}
				else {
					getchar();
					printf("\n잘못된 입력입니다. 다시 입력해주세요.\n\n1. 분반   2. 광운인되기 or 소프트웨어입문세미나   3. 기초 과학   4. 교양   5. 공강 여부   6. 하루 4개 이상의 강의 여부\n\n( 숫자로 입력 ) : ");
					continue;
				}

				printf("\n다시 선택할 것이 더 있나요? ( 네 or 아니오 ) : ");
				getchar();
				while (1) {
					scanf("%s", yn);
					if (strcmp(yn, "네") || strcmp(yn, "아니오")) {
						break;
					}
					else {
						getchar();
						printf("\n잘못된 입력입니다. 다시 입력해주세요. ( 네 or 아니오 ) : ");
					}
				}
				if (strcmp(yn, "아니오")) {
					break;
				}
				printf("\n1. 분반   2. 광운인되기 or 소프트웨어입문세미나   3. 기초 과학   4. 교양   5. 공강 여부   6. 하루 4개 이상의 강의 여부\n\n( 숫자로 입력 ) : ");
			}
			break;
		}
		else if (strcmp(yn, "아니오")) {
			break;
		}
		else {
			getchar();
			printf("\n잘못된 입력입니다. 다시 입력해주세요 ( 네 or 아니오 ) : ");
		}
	}

	int subject_number[4] = { 6, 9, science, ge };//각 그룹별 과목의 수
	printf("\n");
	timetable_made(timetable, subject, 0, subject_number, day_num, lec, lectures, &timetable_number, ge_credits, kw);

	if (timetable_number == 0) {
		while (1) {
			printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("\n조건을 만족하는 시간표가 없습니다. 다시 선택할 것을 골라 주세요.\n\n1. 광운인되기 or 소프트웨어입문세미나   2. 기초 과학   3. 교양   4. 공강 여부   5. 하루 4개 이상의 강의 여부\n\n( 숫자로 입력 ) : ");
			getchar();
			while (1) {
				scanf("%d", &n);
				if (n == 1) {
					kwangwoon(timetable, &kw, lectures);
					break;
				}
				else if (n == 2) {
					science_pick(subject3, &science);
					subject_number[2] = science;
					break;
				}
				else if (n == 3) {
					ge = 0;
					ge_pick(subject4, &ge, ge_credits, lec, day_num);
					subject_number[3] = ge;
					break;
				}
				else if (n == 4) {
					day_off(science, &day_num, kw);
					break;
				}
				else if (n == 5) {
					lectures_4(&lec);
					break;
				}
				else {
					getchar();
					printf("\n잘못된 입력입니다. 다시 입력해주세요.\n\n1. 광운인되기 or 소프트웨어입문세미나   2. 기초 과학   3. 교양   4. 공강 여부   5. 하루 4개 이상의 강의 여부\n\n( 숫자로 입력 ) : ");
				}
			}

			printf("\n");
			timetable_made(timetable, subject, 0, subject_number, day_num, lec, lectures, &timetable_number, ge_credits, kw);

			if (timetable_number != 0)
				break;
		}
	}
	return 0;
}

//문자열 비교 함수
int strcmp(char str1[], char str2[]) {
	int i = 0;
	do {
		if (str1[i] != str2[i])
			return 0;
		i++;
	} while (str2[i - 1] != '\0');

	return 1;
}

//문자열 대입 함수
void strcpy(char str1[], char str2[]) {
	int i = 0;
	do {
		str1[i] = str2[i];
		i++;
	} while (str2[i - 1] != '\0');
}

//과목을 시간표에 넣는 함수
void timetable_input(char timetable[][14], information subject[], int i) {
	int j = 0;
	while (subject[i].time[j] < 30 && j < 3) {
		strcpy(timetable[subject[i].time[j]], subject[i].name);
		j++;
	}
}

//시간표를 출력하는 함수
void timetable_print(char timetable[][14], int timetable_number, int ge_credit, int other_time, char other_name[], int kw) {
	printf("----------------------------------- 시간표 %d ---------------------------------------", timetable_number);
	if (timetable_number < 10)
		printf("--\n");
	else if (timetable_number < 100)
		printf("-\n");
	else
		printf("\n");
	printf("     |      월       |      화       |      수       |      목       |      금       |\n");
	printf("--------------------------------------------------------------------------------------\n");
	for (int i = 0; i < 30; i++) {
		if (i % 5 == 0)
			printf("%d교시", i / 5 + 1);
		printf("| %s ", timetable[i]);
		if (i % 5 == 4)
			printf("|\n");
	}
	printf("--------------------------------------------------------------------------------------");
	if (kw == 1)
		printf("\n비대면 강의 : 광운인되기");

	if (other_time == 36) {
		if (kw == 1)
			printf(", %s\n", other_name);
		else
			printf("\n비대면 강의 : %s\n", other_name);
	}
	else if (other_time == 30) {
		printf("\n월 7, 8, 9 : %s\n", other_name);
	}
	else if (other_time == 31) {
		printf("\n화 7, 8, 9 : %s\n", other_name);
	}
	else if (other_time == 32) {
		printf("\n수 7, 8, 9 : %s\n", other_name);
	}
	else if (other_time == 33) {
		printf("\n목 7, 8, 9 : %s\n", other_name);
	}
	else if (other_time == 34) {
		printf("\n금 7, 8, 9 : %s\n", other_name);
	}
	else if (other_time == 35) {
		printf("\n토 1, 2 : %s\n", other_name);
	}
	else {
		printf("\n");
	}

	if (kw == 1) {
		if (ge_credit == 3)
			printf("필수교양학점 : 7/13 균형교양학점 : 3/9 기초교양학점 : 6/21 주전공학점 : 3/60 졸업이수학점 19/133\n");
		else if (ge_credit == 6)
			printf("필수교양학점 : 7/13 균형교양학점 : 0/9 기초교양학점 : 6/21 주전공학점 : 3/60 졸업이수학점 19/133\n");
		else
			printf("필수교양학점 : 7/13 균형교양학점 : 0/9 기초교양학점 : 6/21 주전공학점 : 3/60 졸업이수학점 %d/133\n", 16 + ge_credit);

		printf("수강신청 순서 : 교양 -> 수학, 과학, 융사글 -> 공설입, C프 -> 광운인되기\n\n");
	}
	else {
		if (ge_credit == 3)
			printf("필수교양학점 : 6/13 균형교양학점 : 3/9 기초교양학점 : 6/21 주전공학점 : 4/60 졸업이수학점 19/133\n");
		else if (ge_credit == 6)
			printf("필수교양학점 : 6/13 균형교양학점 : 0/9 기초교양학점 : 6/21 주전공학점 : 4/60 졸업이수학점 19/133\n");
		else
			printf("필수교양학점 : 6/13 균형교양학점 : 0/9 기초교양학점 : 6/21 주전공학점 : 4/60 졸업이수학점 %d/133\n", 16 + ge_credit);

		printf("수강신청 순서 : 교양, 소프트웨어입문세미나 -> 수학, 과학, 융사글 -> 공설입, C프\n\n");
	}
}

//시간표에 넣었던 과목을 빼는 함수
void timetable_delete(char timetable[][14], information subject[], int i) {
	int j = 0;
	while (subject[i].time[j] < 30 && j < 3) {
		strcpy(timetable[subject[i].time[j]], "             ");
		j++;
	}
}

//시간표를 만드는 함수
void timetable_made(char timetable[][14], information* subject[], int group_number, int subject_number[], int day_num, int lec, int lectures[], int* timetable_number, int ge_credits[], int kw) {

	for (int i = 0; i < subject_number[group_number]; i++) {
		//공강 확인
		if (kw == 0 && day_num == 1)
			continue;
		if (subject[group_number][i].time[0] < 35) {
			if (subject[group_number][i].time[0] % 5 == day_num || subject[group_number][i].time[1] % 5 == day_num || subject[group_number][i].time[2] % 5 == day_num)
				continue;
		}

		//중복인지 확인
		if (subject[group_number][i].time[2] < 30) {
			if (strcmp(timetable[subject[group_number][i].time[0]], "             ") == 0 || strcmp(timetable[subject[group_number][i].time[1]], "             ") == 0 || strcmp(timetable[subject[group_number][i].time[2]], "             ") == 0) {
				continue;
			}
		}
		else if (subject[group_number][i].time[1] < 30) {
			if (strcmp(timetable[subject[group_number][i].time[0]], "             ") == 0 || strcmp(timetable[subject[group_number][i].time[1]], "             ") == 0) {
				continue;
			}
		}
		else if (subject[group_number][i].time[0] < 30) {
			if (strcmp(timetable[subject[group_number][i].time[0]], "             ") == 0) {
				continue;
			}
		}

		//하루에 4개 이상의 강의가 있는지 확인
		if (lec == 1) {
			for (int j = 0; subject[group_number][i].time[j] < 35 && j < 3; j++) {
				lectures[subject[group_number][i].time[j] % 5] += 1;
			}

			if (lectures[subject[group_number][i].time[0] % 5] >= 4 || lectures[subject[group_number][i].time[1] % 5] >= 4 || lectures[subject[group_number][i].time[2] % 5] >= 4) {
				for (int j = 0; subject[group_number][i].time[j] < 35 && j < 3; j++) {
					lectures[subject[group_number][i].time[j] % 5] -= 1;
				}
				continue;
			}
		}

		timetable_input(timetable, subject[group_number], i);

		if (group_number != 3) {
			timetable_made(timetable, subject, group_number + 1, subject_number, day_num, lec, lectures, timetable_number, ge_credits, kw);
		}
		else {
			(*timetable_number)++;
			timetable_print(timetable, *timetable_number, ge_credits[i], subject[group_number][i].time[0], subject[group_number][i].name, kw);
		}

		if (lec == 1) {
			for (int j = 0; subject[group_number][i].time[j] < 35 && j < 3; j++) {
				lectures[subject[group_number][i].time[j] % 5] -= 1;
			}
		}
		timetable_delete(timetable, subject[group_number], i);
	}
}

//분반 선택
void class_pick(char timetable[][14], char cls[]) {
	printf("\n분반을 입력하세요.( C4 or C5 or C6 ) : ");
	while (1) {
		scanf("%s", cls);

		if (strcmp(cls, "c4") || strcmp(cls, "C4")) {
			strcpy(timetable[15], "C   프 임재한");
			strcpy(timetable[12], "C   프 임재한");
			break;
		}
		else if (strcmp(cls, "c5") || strcmp(cls, "C5")) {
			strcpy(timetable[20], "C   프 임재한");
			strcpy(timetable[27], "C   프 임재한");
			break;
		}
		else if (strcmp(cls, "c6") || strcmp(cls, "C6")) {
			strcpy(timetable[25], "C   프 안우현");
			strcpy(timetable[22], "C   프 안우현");
			break;
		}
		else {
			getchar();
			printf("\n잘못된 입력입니다. 다시 입력해주세요. ( C4 or C5 or C6 ) : ");
		}
	}
}

//광운인되기 or 소프트웨어입문세미나 선택
void kwangwoon(char timetable[][14], int* kw, int lectures[]) {
	char str[21] = " ";

	printf("\n둘 중 어느것을 들으시겠습니까? ( 광운인되기 or 소프트웨어입문세미나 ) : ");
	getchar();
	while (1) {
		scanf("%s", str);

		if (strcmp(str, "광운인되기")) {
			strcpy(timetable[16], "             ");
			lectures[1] = 0;
			*kw = 1;
			break;
		}
		else if (strcmp(str, "소프트웨어입문세미나")) {
			strcpy(timetable[16], "소프트 이강훈");
			lectures[1] = 1;
			*kw = 0;
			break;
		}
		else {
			getchar();
			printf("\n잘못된 입력입니다. 다시 입력해주세요. ( 광운인되기 or 소프트웨어입문세미나 ) : ");
		}
	}
}

//기초과학 선택
void science_pick(information subject[], int* science) {
	char str[16] = " ";
	printf("\n듣고 싶은 기초과학 과목을 입력하세요. ( 대학물리학1 or 대학화학및실험1 ) : ");
	getchar();
	while (1) {
		scanf("%s", str);

		if (strcmp(str, "대학물리학1")) {
			strcpy(subject[0].name, "대물 1 이건준");
			subject[0].time[0] = 25;
			subject[0].time[1] = 22;
			subject[0].time[2] = 37;
			strcpy(subject[1].name, "대물 1 백구연");
			subject[1].time[0] = 15;
			subject[1].time[1] = 12;
			subject[1].time[2] = 37;
			strcpy(subject[2].name, "대물 1 구제환");
			subject[2].time[0] = 1;
			subject[2].time[1] = 8;
			subject[2].time[2] = 37;
			*science = 3;
			break;
		}
		else if (strcmp(str, "대학화학및실험1")) {
			strcpy(subject[0].name, "화실 1 최  한");
			subject[0].time[0] = 11;
			subject[0].time[1] = 16;
			subject[0].time[2] = 18;
			strcpy(subject[1].name, "화실 1 최  한");
			subject[1].time[0] = 21;
			subject[1].time[1] = 26;
			subject[1].time[2] = 28;
			*science = 2;
			break;
		}
		else {
			getchar();
			printf("\n잘못된 입력입니다. 다시 입력해주세요. ( 대학물리학1 or 대학화학및실험1 ) : ");
		}
	}
}

//균형교양 선택
void ge_pick(information subject[], int* ge, int ge_credits[], int lec, int day_num) {
	typedef struct {
		char name_full[50];//과목명 및 교수명 풀네임
		char name[14]; //과목명 및 교수명 줄임말
		int time[2][3]; //분반별 시간
		int credit; //학점
	} information_ge;

	information_ge ge1[27] = {
		{ "공학과디자인 유미란", "공학과 유미란", { { 21, 28, 37 }, { 26, 23, 37 } }, 3 },
		{ "공학교양세미나 김충혁", "공학교 김충혁", { { 0, 5, 37 }, { 37, 37, 37 } }, 3 },
		{ "공학교양세미나 권순철", "공학교 권순철", { { 21, 28, 37 }, { 37, 37, 37 } }, 3 },
		{ "사진편집기술 하마처", "사진편 하마처", { { 18, 37, 37 }, { 37, 37, 37 } }, 3 },
		{ "생명과기술 박경순", "생명과 박경순", { { 25, 22, 37 }, { 37, 37, 37 } }, 3 },
		{ "생활속의과학 이도남", "생활속 이도남", { { 15, 12, 37 }, { 11, 18, 37 } }, 3 },
		{ "생활속의과학(비대면) 김충혁", "생활속 김충혁", { { 36, 36, 36 }, { 37, 37, 37 } }, 3 },
		{ "심층탐구자연의이해(비대면) 김영희", "심층탐 김영희", { { 36, 36, 36 }, { 37, 37, 37 } }, 1 },
		{ "자연교양세미나 김영희", "자연교 김영희", { { 25, 22, 37 }, { 37, 37, 37 } }, 3 },
		{ "자연교양세미나 이영수", "자연교 이영수", { { 25, 22, 37 }, { 37, 37, 37 } }, 3 },
		{ "컴퓨터활용 정계동", "컴퓨터 정계동", { { 21, 28, 37 }, { 37, 37, 37 } }, 3 },
		{ "파이썬프로그래밍기초 이강성", "파이썬 이강성", { { 0, 7, 37 }, { 5, 2, 37 } }, 3 },
		{ "빅데이터의이해 최희식", "빅데이 최희식", { { 1, 8, 37 }, { 6, 3, 37 } }, 3 },
		{ "수학과철학의대화 최종성", "수학과 최종성", { { 20, 27, 37 }, { 37, 37, 37 } }, 3 },
		{ "신기술과미래사회 김충혁", "신기술 김충혁", { { 20, 37, 37 }, { 37, 37, 37 } }, 3 },
		{ "인공지능의이해(비대면) 서영호", "인공지 서영호", { { 36, 36, 36 }, { 37, 37, 37 } }, 3 },
		{ "인공지능의이해 한진섭", "인공지 한진섭", { { 14, 19, 37 }, { 37, 37, 37 } }, 3 },
		{ "인터넷활용 김진수", "인터넷 김진수", { { 14, 19, 37 }, { 24, 29, 37 } }, 3 },
		{ "자연과학사 박봉주", "자연과 박봉주", { { 16, 13, 37 }, { 37, 37, 37 } }, 3 },
		{ "자연과학사 박경순", "자연과 박경순", { { 21, 28, 37 }, { 37, 37, 37 } }, 3 },
		{ "패러독스와논리 최종성", "패러독 최종성", { { 25, 22, 37 }, { 37, 37, 37 } }, 3 },
		{ "환경과생태 양재규", "환경과 양재규", { { 30, 30, 30 }, { 37, 37, 37 } }, 3 },
		{ "디지털사회를위한데이터분석 이강성", "디지털 이강성", { { 15, 12, 37 }, { 37, 37, 37 } }, 3 },
		{ "미디어아트 이상민", "미디어 이상민", { { 15, 12, 37 }, { 37, 37, 37 } }, 3 },
		{ "산업화와환경오염 종초은", "산업화 종초은", { { 21, 28, 37 }, { 26, 23, 37 } }, 3 },
		{ "정보사회와수학 김영희", "정보사 김영희", { { 20, 27, 37 }, { 37, 37, 37 } }, 3 },
		{ "예술과과학의융합 김미수", "예술과 김미수", { { 25, 22, 37 }, { 37, 37, 37 } }, 3 }
	};

	information_ge ge2[28] = {
		{ "과학기술윤리 이재유", "과학기 이재유", { { 11, 18, 37 }, { 37, 37, 37 } }, 3 },
		{ "과학기술윤리 박지희", "과학기 박지희", { { 24, 29, 37 }, { 37, 37, 37 } }, 3 },
		{ "과학철학의이해 박신화", "과학철 박신화", { { 1, 8, 37 }, { 6, 3, 37 } }, 3 },
		{ "나의역사 김희교", "나의역 김희교", { { 21, 28, 37 }, { 37, 37, 37 } }, 3 },
		{ "논리적으로사고하기 이경희", "논리적 이경희", { { 14, 19, 37 }, { 24, 29, 37 } }, 3 },
		{ "동서양신화읽기와변용 고경주", "동서양 고경주", { { 2, 7, 37 }, { 37, 37, 37 } }, 3 },
		{ "동양의역사 김동찬", "동양의 김동찬", { { 20, 27, 37 }, { 37, 37, 37 } }, 3 },
		{ "세계화시대의역사보기 김동찬", "세계화 김동찬", { { 25, 22, 37 }, { 37, 37, 37 } }, 3 },
		{ "심층탐구인간의이해(비대면) 김인호", "심층탐 김인호", { { 36, 36, 36 }, { 37, 37, 37 } }, 3 },
		{ "영화로읽는서양문학 노진서", "영화로 노진서", { { 26, 23, 37 }, { 37, 37, 37 } }, 3 },
		{ "유럽의과거와현재 김동조", "유럽의 김동조", { { 26, 23, 37 }, { 37, 37, 37 } }, 3 },
		{ "인간존재의이해 이승준", "인간존 이승준", { { 4, 9, 37 }, { 37, 37, 37 } }, 3 },
		{ "인간존재의이해 이지영", "인간존 이지영", { { 20, 27, 37 }, { 37, 37, 37 } }, 3 },
		{ "인문교양세미나 김정권", "인문교 김정권", { { 30, 30, 30 }, { 37, 37, 37 } }, 3 },
		{ "현대사회와윤리 김상원", "현대사 김상원", { { 1, 6, 37 }, { 37, 37, 37 } }, 3 },
		{ "공감적소통연구 박지희", "공감적 박지희", { { 14, 19, 37 }, { 37, 37, 37 } }, 3 },
		{ "과학기술시대의생명과신체 이승준", "과학기 이승준", { { 24, 29, 37 }, { 37, 37, 37 } }, 3 },
		{ "미국의과거와현재 김민수", "미국의 김민수", { { 2, 7, 37 }, { 37, 37, 37 } }, 3 },
		{ "미디어로읽는영어의역사 노진서", "미디어 노진서", { { 20, 27, 37 }, { 37, 37, 37 } }, 3 },
		{ "세계도시문명사 차승현", "세계도 차승현", { { 0, 7, 37 }, { 37, 37, 37 } }, 3 },
		{ "세계문화의이해(비대면) 장수현", "세계문 장수현", { { 36, 36, 36 }, { 37, 37, 37 } }, 3 },
		{ "인물로본한국사 김희교", "인물로 김희교", { { 4, 9, 37 }, { 37, 37, 37 } }, 3 },
		{ "자아의이해와문학치료 도기숙", "자아의 도기숙", { { 37 }, { 37, 37, 37 } }, 3 },
		{ "한국근현대사 김정권", "한국근 김정권", { { 0, 7, 37 }, { 5, 2, 37 } }, 3 },
		{ "르네상스문화와과학 차승현", "르네상 차승현", { { 5, 2, 37 }, { 37, 37, 37 } }, 3 },
		{ "문예작품으로읽는서양문명사 노진서", "문예작 노진서", { { 21, 28, 37 }, { 37, 37, 37 } }, 3 },
		{ "우리시대의삶과문학 김미정", "우리시 김미정", { { 0, 5, 37 }, { 37, 37, 37 } }, 3 },
		{ "한국과학기술문명사 김인호", "한국과 김인호", { { 0, 7, 37 }, { 37, 37, 37 } }, 3 }
	};

	information_ge ge3[30] = {
		{ "경제와경영 송영출", "경제와 송영출", { { 24, 29, 30 }, { 37, 37, 37 } }, 3 },
		{ "글로벌시대의쟁점과현안 남정호", "글로벌 남정호", { { 14, 19, 37 }, { 37, 37, 37 } }, 3 },
		{ "기술경영과마케팅 김찬모", "기술경 김찬모", { { 21, 28, 37 }, { 26, 23, 37 } }, 3 },
		{ "법과생활 손명지", "법과생 손명지", { { 11, 18, 37 }, { 37, 37, 37 } }, 3 },
		{ "사회과학교양세미나 하마처", "사회과 하마처", { { 13, 37, 37 }, { 37, 37, 37 } }, 3 },
		{ "사회과학교양세미나 김일식", "사회과 김일식", { { 2, 7, 37 }, { 37, 37, 37 } }, 3 },
		{ "사회봉사1 임안나", "사회봉 임안나", { { 35, 35, 35 }, { 37, 37, 37 } }, 1 },
		{ "생활속의경제 이수옥", "생활속 이수옥", { { 20, 27, 37 }, { 37, 37, 37 } }, 3 },
		{ "생활속의경제 김일식", "생활속 김일식", { { 1, 8, 37 }, { 37, 37, 37 } }, 3 },
		{ "생활속의회계와세무 이수욱", "생활속 이수욱", { { 25, 22, 37 }, { 37, 37, 37 } }, 3 },
		{ "성과심리학 이정은", "성과심 이정은", { { 4, 9, 37 }, { 14, 19, 37 } }, 3 },
		{ "인간심리의이해 김기년", "인간심 김기년", { { 4, 9, 37 }, { 37, 37, 37 } }, 3 },
		{ "세계경제의이해 김일식", "세계경 김일식", { { 6, 3, 37 }, { 37, 37, 37 } }, 3 },
		{ "정치와현대사회 기유정", "정치와 기유정", { { 24, 29, 37 }, { 37, 37, 37 } }, 3 },
		{ "21세기동아시아사회의이해 공준환", "21세기 공준환", { { 1, 8, 37 }, { 6, 3, 37 } }, 3 },
		{ "국가와행정 서승현", "국가와 서승현", { { 24, 29, 37 }, { 37, 37, 37 } }, 3 },
		{ "국가와행정 최영훈", "국가와 최영훈", { { 25, 22, 37 }, { 37, 37, 37 } }, 3 },
		{ "미디어활용과생활 레이몬드", "미디어 레이몬", { { 21, 37, 37 }, { 26, 37, 37 } }, 3 },
		{ "범죄와사회 강희창", "범죄와 강희창", { { 32, 32, 32 }, { 37, 37, 37 } }, 3 },
		{ "법과경제 손명지", "법과경 손명지", { { 16, 13, 37 }, { 37, 37, 37 } }, 3 },
		{ "법과권리 한재경", "법과권 한재경", { { 26, 23, 37 }, { 37, 37, 37 } }, 3 },
		{ "법과정치 남정아", "법과정 남정아", { { 2, 7, 37 }, { 37, 37, 37 } }, 3 },
		{ "법논리학 이춘원", "법논리 이춘원", { { 4, 9, 37 }, { 37, 37, 37 } }, 3 },
		{ "진로탐색(비대면) 김정권", "진로탐 김정권", { { 36, 36, 36 }, { 37, 37, 37 } }, 2 },
		{ "현대사회와인권 문수경", "현대사 문수경", { { 22, 27, 37 }, { 37, 37, 37 } }, 3 },
		{ "경제신문읽기 이은정", "경제신 이은정", { { 11, 18, 37 }, { 16, 13, 37 } }, 3 },
		{ "스타트업과고객발굴전략 이경학", "스타트 이경학", { { 22, 27, 37 }, { 37, 37, 37 } }, 3 },
		{ "여성과남성 도기숙", "여성과 도기숙", { { 18, 37, 37 }, { 37, 37, 37 } }, 3 },
		{ "취업전략(비대면) 김정권", "취업전 김정권", { { 36, 36, 36 }, { 37, 37, 37 } }, 2 },
		{ "취업전략(대면) 김정권", "취업전 김정권", { { 11, 18, 37 }, { 37, 37, 37 } }, 2 }
	};

	information_ge ge4[37] = {
		{ "독일어1 조규희", "독일 1 조규희", { { 11, 18, 37 }, { 16, 13, 37 } }, 3 },
		{ "스페인어1 남영우", "스페 1 남영우", { { 11, 18, 37 }, { 21, 28, 37 } }, 3 },
		{ "일본문화읽기 유양근", "일문읽 유양근", { { 21, 26, 37 }, { 37, 37, 37 } }, 3 },
		{ "일본문화읽기 권혁인", "일문읽 권혁인", { { 26, 23, 37 }, { 37, 37, 37 } }, 3 },
		{ "일본어듣기와쓰기 권혁인", "일듣쓰 권혁인", { { 21, 28, 37 }, { 1, 8, 37 } }, 3 },
		{ "중국어듣기와쓰기 이명숙", "중듣쓰 이명숙", { { 20, 27, 37 }, { 37, 37, 37 } }, 3 },
		{ "초급일본어1 김희성", "초일 1 김희성", { { 21, 28, 37 }, { 31, 31, 31 } }, 3 },
		{ "초급일본어1 김덕미", "초일 1 김덕미", { { 11, 18, 37 }, { 37, 37, 37 } }, 3 },
		{ "초급일본어1 박세희", "초일 1 박세희", { { 26, 23, 37 }, { 37, 37, 37 } }, 3 },
		{ "초급일본어1 이지은", "초일 1 이지은", { { 4, 9, 37 }, { 14, 19, 37 } }, 3 },
		{ "초급일본어1 후지무라마이", "초일 1 후지무", { { 15, 12, 37 }, { 11, 18, 37 } }, 3 },
		{ "초급일본어1 다와라기하루미", "초일 1 다와라", { { 5, 2, 37 }, { 37, 37, 37 } }, 3 },
		{ "초급일본어1 성호현", "초일 1 성호현", { { 16, 13, 37 }, { 37, 37, 37 } }, 3 },
		{ "초급일본어1 최정아", "초일 1 최정아", { { 25, 22, 37 }, { 37, 37, 37 } }, 3 },
		{ "초급일본어1 이승영", "초일 1 이승영", { { 20, 27, 37 }, { 37, 37, 37 } }, 3 },
		{ "초급일본어2 이승영", "초일 2 이승영", { { 7, 37, 37 }, { 37, 37, 37 } }, 3 },
		{ "초급일본어생활한자 다와라기하루미", "초일생 다와라", { { 20, 27, 37 }, { 37, 37, 37 } }, 3 },
		{ "초급중국어1 곡효운", "초중 1 곡효운", { { 0, 7, 37 }, { 5, 2, 37 } }, 3 },
		{ "초급중국어1 김태경", "초중 1 김태경", { { 11, 18, 37 }, { 16, 13, 37 } }, 3 },
		{ "초급중국어1 성은리", "초중 1 성은리", { { 26, 23, 37 }, { 37, 37, 37 } }, 3 },
		{ "초급중국어1 장가원", "초중 1 장가원", { { 1, 8, 37 }, { 37, 37, 37 } }, 3 },
		{ "초급중국어1 김수정", "초중 1 김수정", { { 30, 30, 30 }, { 37, 37, 37 } }, 3 },
		{ "초급중국어2 김수정", "초중 2 김수정", { { 20, 27, 37 }, { 37, 37, 37 } }, 3 },
		{ "현대중국의문화트렌드 곡효운", "현중문 곡효운", { { 6, 37, 37 }, { 37, 37, 37 } }, 3 },
		{ "현대중국의문화트렌드 박현곤", "현중문 박현곤", { { 1, 8, 37 }, { 37, 37, 37 } }, 3 },
		{ "HSK연습 이명숙", "HSK연  이명숙", { { 25, 22, 37 }, { 37, 37, 37 } }, 3 },
		{ "JLPT연습 권혁인", "JLPT연 권혁인", { { 6, 3, 37 }, { 37, 37, 37 } }, 3 },
		{ "생활일본어회화 다와라기하루미", "생일회 다와라", { { 25, 22, 37 }, { 37, 37, 37 } }, 3 },
		{ "생활한문 김지현", "생활한 김지현", { { 11, 18, 37 }, { 16, 13, 37 } }, 3 },
		{ "생활한문 김준", "생활한 김준", { { 26, 23, 37 }, { 37, 37, 37 } }, 3 },
		{ "생활한문 이철희", "생활한 이철희", { { 20, 27, 37 }, { 25, 22, 37 } }, 3 },
		{ "스크린일본어 유양근", "스크일 유양근", { { 31, 31, 31 }, { 37, 37, 37 } }, 3 },
		{ "스크린일본어 후지무라마이", "스크일 후지무", { { 21, 28, 37 }, { 37, 37, 37 } }, 3 },
		{ "시청각중국어 장중레이", "시청중 장중레", { { 11, 18, 37 }, { 37, 37, 37 } }, 3 },
		{ "실용일본어문법 이승영", "실일문 이승영", { { 5, 37, 37 }, { 37, 37, 37 } }, 3 },
		{ "실용중국어문법 곡효운", "실중문 곡효운", { { 11, 37, 37 }, { 37, 37, 37 } }, 3 },
		{ "중국문화지리 전보옥", "중문지 전보옥", { { 5, 37, 37 }, { 37, 37, 37 } }, 3 }
	};

	information_ge ge5[30] = {
		{ "골프(실기) 김재형", "골  프 김재형", { { 14, 19, 37 }, { 24, 29, 37 } }, 2 },
		{ "수상스키(실기) 설수황", "수상스 김재형", { { 20, 25, 37 }, { 37, 37, 37 } }, 2 },
		{ "스포츠피싱(실기) 민병진", "스피싱 민병진", { { 13, 18, 37 }, { 37, 37, 37 } }, 2 },
		{ "요가(실기) 홍승연", "요  가 홍승연", { { 1, 6, 37 }, { 11, 16, 37 } }, 2 },
		{ "웰니스트레이닝(실기) 최재영", "웰트닝 최재영", { { 20, 25, 37 }, { 37, 37, 37 } }, 2 },
		{ "윈드서핑(실기) 유정완", "윈드서 유정완", { { 3, 8, 37 }, { 37, 37, 37 } }, 2 },
		{ "축구(실기) 염종훈", "축  구 염종훈", { { 22, 27, 37 }, { 37, 37, 37 } }, 2 },
		{ "탁구(실기) 박현애", "탁  구 박현애", { { 6, 11, 37 }, { 16, 21, 37 } }, 2 },
		{ "교양음악실기1(바이올린)(실기) 배윤진", "바이올 배윤진", { { 20, 25, 37 }, { 37, 37, 37 } }, 6 },
		{ "교양음악실기1(첼로)(실기) 정연재", "첼  로 정연재", { { 20, 25, 37 }, { 37, 37, 37 } }, 6 },
		{ "교양음악실기1(클라리넷)(실기) 김진규", "클라리 김진규", { { 6, 11, 37 }, { 37, 37, 37 } }, 6 },
		{ "교양음악실기1(키보드테크닉)(실기) 김철수", "키보드 김철수", { { 3, 8, 37 }, { 37, 37, 37 } }, 6 },
		{ "아카펠라1(실기) 이강성", "아펠 1 이강성", { { 22, 27, 37 }, { 37, 37, 37 } }, 6 },
		{ "드로잉(실기) 김문석", "드로잉 김문석", { { 22, 27, 37 }, { 37, 37, 37 } }, 6 },
		{ "드로잉(실기) 윤지현", "드로잉 윤지현", { { 11, 16, 37 }, { 37, 37, 37 } }, 6 },
		{ "대중문화와삶 하효숙", "대문삶 하효숙", { { 26, 23, 37 }, { 31, 31, 31 } }, 3 },
		{ "심층탐구예술의이해 노정진", "심탐예 노정진", { { 22, 27, 37 }, { 37, 37, 37 } }, 1 },
		{ "영화의이해 이대범", "영화의 이대범", { { 20, 25, 37 }, { 30, 30, 30 } }, 3 },
		{ "교양음악실기2(바이올린)(실기) 배윤진", "바이올 배윤진", { { 21, 26, 37 }, { 37, 37, 37 } }, 6 },
		{ "교양음악실기2(클래식기타)(실기) 유태성", "클기타 유태성", { { 20, 25, 37 }, { 37, 37, 37 } }, 6 },
		{ "실내악앙상블(실기) 김진규", "실내악 김진규", { { 16, 21, 37 }, { 37, 37, 37 } }, 6 },
		{ "일러스트레이션(실기) 김문석", "일러레 김문석", { { 2, 7, 37 }, { 37, 37, 37 } }, 6 },
		{ "일러스트레이션(실기) 윤지현", "일러레 윤지현", { { 21, 26, 37 }, { 37, 37, 37 } }, 6 },
		{ "대중음악의역사(비대면) 김철수", "대중음 김철수", { { 36, 36, 36 }, { 37, 37, 37 } }, 3 },
		{ "전통재즈의역사 노정진", "전재역 노정진", { { 7, 37, 37 }, { 37, 37, 37 } }, 3 },
		{ "한국의문화유산 김형근", "한문유 김형근", { { 0, 7, 37 }, { 37, 37, 37 } }, 3 },
		{ "현대사회와스포츠 한지영", "현사스 한지영", { { 23, 28, 37 }, { 37, 37, 37 } }, 3 },
		{ "현대사회와스포츠 강지연", "현사스 강지연", { { 30, 30, 30 }, { 37, 37, 37 } }, 3 },
		{ "생활속의디자인(비대면) 김문석", "생활속 김문석", { { 36, 36, 36 }, { 37, 37, 37 } }, 3 },
		{ "운동과건강 이시은", "운동과 이시은", { { 3, 8, 37 }, { 37, 37, 37 } }, 3 }
	};

	information_ge* gearr[5] = { ge1, ge2, ge3, ge4, ge5 };
	int size[5] = { 27, 28, 30, 37, 30 };
	printf("\n교양 후보 3가지를 선택해주세요.\n\n3학점이 아닌 과목과 실습 과목은 균형교양으로 인정되지 않으니 주의해주세요.\n");

	int forr = 1;
	if (lec == 1) {
		forr++;
	}
	if (day_num != 99) {
		forr++;
	}

	for (int i = 0; i < forr; i++) {
		int n = 0;
		int nn = 0;
		printf("\n듣고싶은 교양 영역을 입력해주세요.\n\n1. 과학과 기술   2. 인간과 철학   3. 사회와 경제   4. 글로벌 문화와 제2 외국어   5. 예술과 체육\n\n( 숫자로 입력 ) : ");
		getchar();
		while (1) {
			scanf("%d", &n);
			if (n >= 1 && n <= 5) {
				break;
			}
			else {
				getchar();
				printf("\n잘못된 입력입니다. 다시 입력해주세요. ( 숫자로 입력 ) : ");
			}
		}
		n--;

		for (int j = 0; j < size[n]; j++) {
			if (j % 3 == 0) {
				printf("\n\n");
			}
			if (gearr[n][j].credit == 6)
				printf("%2d. %-40s (%d학점) ", j + 1, gearr[n][j].name_full, gearr[n][j].credit / 2);
			else
				printf("%2d. %-40s (%d학점) ", j + 1, gearr[n][j].name_full, gearr[n][j].credit);
		}

		printf("\n\n듣고싶은 교양 과목을 선택해주세요. ( 숫자로 입력 ) : ");
		getchar();
		while (1) {
			scanf("%d", &nn);
			if (nn <= size[n] && nn > 0) {
				break;
			}
			else {
				getchar();
				printf("\n잘못된 입력입니다. 다시 입력해주세요. ( 숫자로 입력 ) : ");
			}
		}
		nn--;

		strcpy(subject[*ge].name, gearr[n][nn].name);
		for (int j = 0; j < 3; j++) {
			subject[*ge].time[j] = gearr[n][nn].time[0][j];
		}
		ge_credits[*ge] = gearr[n][nn].credit;
		(*ge)++;

		if (gearr[n][nn].time[1][0] != 37) {
			strcpy(subject[*ge].name, gearr[n][nn].name);
			for (int j = 0; j < 3; j++) {
				subject[*ge].time[j] = gearr[n][nn].time[1][j];
			}
			ge_credits[*ge] = gearr[n][nn].credit;
			(*ge)++;
		}
	}
}

//공강 여부 확인
void day_off(int science, int* day_num, int kw) {
	char str[7] = " ";

	if (science == 2) {
		printf("\n금요일을 공강으로 하겠습니까? ( 네 or 아니오 ) : ");
		getchar();
		while (1) {
			scanf("%s", str);

			if (strcmp(str, "네")) {
				*day_num = 4;
				break;
			}
			else if (strcmp(str, "아니오")) {
				*day_num = 99;
				break;
			}
			else {
				getchar();
				printf("\n잘못된 입력입니다. 다시 입력해주세요. ( 네 or 아니오 ) : ");
			}
		}
	}
	else {
		if (kw == 0) {
			printf("\n공강으로 하고 싶은 요일이 있나요? ( 네 or 아니오 ) ( 목요일, 금요일만 가능합니다. ) : ");
			getchar();
			while (1) {
				scanf("%s", str);

				if (strcmp(str, "네")) {
					printf("\n어떤 요일 인가요? ( 목 or 금 ) : ");
					getchar();
					while (1) {
						scanf("%s", str);

						if (strcmp(str, "목")) {
							*day_num = 3;
							break;
						}
						else if (strcmp(str, "금")) {
							*day_num = 4;
							break;
						}
						else {
							getchar();
							printf("\n잘못된 입력입니다. 다시 입력해주세요. ( 목 or 금 ) : ");
						}
					}
					break;
				}
				else if (strcmp(str, "아니오")) {
					*day_num = 99;
					break;
				}
				else {
					getchar();
					printf("\n잘못된 입력입니다. 다시 입력해주세요. ( 네 or 아니오 ) : ");
				}
			}
		}
		else {
			printf("\n공강으로 하고 싶은 요일이 있나요? ( 네 or 아니오 ) ( 화요일, 목요일, 금요일만 가능합니다. ) : ");
			getchar();
			while (1) {
				scanf("%s", str);

				if (strcmp(str, "네")) {
					printf("\n어떤 요일 인가요? ( 화 or 목 or 금 ) : ");
					getchar();
					while (1) {
						scanf("%s", str);

						if (strcmp(str, "화")) {
							*day_num = 1;
							break;
						}
						else if (strcmp(str, "목")) {
							*day_num = 3;
							break;
						}
						else if (strcmp(str, "금")) {
							*day_num = 4;
							break;
						}
						else {
							getchar();
							printf("\n잘못된 입력입니다. 다시 입력해주세요. ( 화 or 목 or 금 ) : ");
						}
					}
					break;
				}
				else if (strcmp(str, "아니오")) {
					*day_num = 99;
					break;
				}
				else {
					getchar();
					printf("\n잘못된 입력입니다. 다시 입력해주세요. ( 네 or 아니오 ) : ");
				}
			}
		}
	}
}

//하루에 4개 이상의 강의 포함 여부
void lectures_4(int* lec) {
	char str[7] = " ";
	printf("\n하루에 4개 이상의 강의가 포함되어 있어도 괜찮습니까? ( 네 or 아니오 ) : ");
	getchar();
	while (1) {
		scanf("%s", str);

		if (strcmp(str, "네")) {
			*lec = 0;
			break;
		}
		else if (strcmp(str, "아니오")) {
			*lec = 1;
			break;
		}
		else {
			getchar();
			printf("\n잘못된 입력입니다. 다시 입력해주세요. ( 네 or 아니오 ) : ");
		}
	}
}