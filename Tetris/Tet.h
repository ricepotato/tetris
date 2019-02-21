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

void InitializeTET( TETRIS *Tet ); // ��Ʈ������ �ʱ�ȭ�մϴ�.
void PutBlockInTET( TETRIS *Tet, int nShape ); // Shape �� �ش��ϴ� ����� ��Ʈ�� ���� �÷������ϴ�.
int MoveBlocks( TETRIS *Tet, int nDirection ); // ����� nDirection �� ���� ���� �����Դϴ�.
int RotateBlocks( TETRIS *Tet ); // ����� �����ϴ�.
int MakeSolidBlocks( TETRIS *Tet ); // �����̴� ����� �������� �ʴ� ������� �ٲߴϴ�.
int DropBlocks( TETRIS *Tet ); // �����̴� ����� ���� �Ʒ��� �����ϴ�.
int MakeTransparentBlocks( TETRIS *Tet ); // ����� ������ ��ġ�� �����ؼ� �� �ڸ��� ������ ����� ǥ�����ݴϴ�.
BOOL PrePutBlock( TETRIS *Tet ); 
void MakeSolidBlocksStraight( TETRIS *Tet ); // �ٷ� �ٴڿ� �����ִ� �Լ�
void EraseLine( TETRIS *Tet ); // ������ �����ִ� �Լ�
void MakeBlockOrder( int *arBckOrder );
void ScoreBoard( TETRIS *Tet );

enum {OI = 1, NIEUN, NUEUNR, LIGHTNING, LIGHTNINGR, UO, NEMO};
#define MAX_NUM_OF_BLOCK_ORDER 10000