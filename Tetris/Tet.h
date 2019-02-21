typedef struct _tet TETRIS;
struct _tet
{
	int arTet[240];
	int nCurrentBlockShape;
	int nCurrentBlockState;
	int nXpos;
	int nYpos;

	int Moving[4];
	int Transparent[4];
	int arScore[13];

	int nScore;
	int nSpeed;
};

void InitializeTET( TETRIS *Tet ); // 테트리스를 초기화합니다.
void PutBlockInTET( TETRIS *Tet, int nShape ); // Shape 에 해당하는 블록을 테트판 위에 올려놓습니다.
int MoveBlocks( TETRIS *Tet, int nDirection ); // 블록을 nDirection 의 값에 따라 움직입니다.
int RotateBlocks( TETRIS *Tet ); // 블록을 돌립니다.
int MakeSolidBlocks( TETRIS *Tet ); // 움직이는 블록을 움직이지 않는 블록으로 바꿉니다.
int DropBlocks( TETRIS *Tet ); // 움직이는 블록을 가장 아래에 놓습니다.
int MakeTransparentBlocks( TETRIS *Tet ); // 블록이 떨어질 위치를 예측해서 그 자리에 투명한 블록을 표시해줍니다.
BOOL PrePutBlock( TETRIS *Tet ); 
void MakeSolidBlocksStraight( TETRIS *Tet ); // 바로 바닥에 내려주는 함수
void EraseLine( TETRIS *Tet ); // 라인을 지워주는 함수
void MakeBlockOrder( int *arBckOrder );
void ScoreBoard( TETRIS *Tet );

enum {OI = 1, NIEUN, NUEUNR, LIGHTNING, LIGHTNINGR, UO, NEMO};
#define MAX_NUM_OF_BLOCK_ORDER 10000