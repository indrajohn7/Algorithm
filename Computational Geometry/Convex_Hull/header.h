typedef struct start_pt
{
	int x_c;
	int y_c;
	int start;
}Start_pt;

typedef struct end_pt
{
	int x_co;
	int y_co;
	int end;
}End_pt;

typedef struct segment
{
	Start_pt st_pt;
	End_pt en_pt;
}Segment;
