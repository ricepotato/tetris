#include<windows.h>
#include"Tet.h"

int Oi[2][16] = {	
	1,0,0,0,	
	1,0,0,0,	
	1,0,0,0,	
	1,0,0,0,

	0,0,0,0,	
	0,0,0,0,	
	0,0,0,0,	
	1,1,1,1
};
int Nieun[4][16] ={	
	0,0,0,0,	
	2,0,0,0,	
	2,0,0,0,	
	2,2,0,0,

	0,0,0,0,	
	0,0,0,0,	
	0,0,2,0,	
	2,2,2,0,

	0,0,0,0,	
	2,2,0,0,	
	0,2,0,0,	
	0,2,0,0,

	0,0,0,0,	
	0,0,0,0,	
	2,2,2,0,	
	2,0,0,0
};
int NieunR[4][16] = 
{
	0,0,0,0,
	0,3,0,0,
	0,3,0,0,
	3,3,0,0,

	0,0,0,0,
	0,0,0,0,
	3,3,3,0,
	0,0,3,0,

	0,0,0,0,
	3,3,0,0,
	3,0,0,0,
	3,0,0,0,

	0,0,0,0,
	0,0,0,0,
	3,0,0,0,
	3,3,3,0
};
int Lightning[2][16] = 
{
	0,0,0,0,
	4,0,0,0,
	4,4,0,0,
	0,4,0,0,

	0,0,0,0,
	0,0,0,0,
	0,4,4,0,
	4,4,0,0
};

int LightningR[2][16] = 
{
	0,0,0,0,
	0,5,0,0,
	5,5,0,0,
	5,0,0,0,

	0,0,0,0,
	0,0,0,0,
	5,5,0,0,
	0,5,5,0
};
int Uo[4][16] = 
{
	0,0,0,0,
	6,6,6,0,
	0,6,0,0,

	0,0,0,0,
	6,0,0,0,
	6,6,0,0,
	6,0,0,0,

	0,0,0,0,
	0,0,0,0,
	0,6,0,0,
	6,6,6,0,

	0,0,0,0,
	0,6,0,0,
	6,6,0,0,
	0,6,0,0
};

int Nemo[16] = 
{
	0,0,0,0,
	0,0,0,0,
	7,7,0,0,
	7,7,0,0
};


int MoveBlocks( TETRIS *Tet, int nDirection )
{
	/*
	����� ����� ���������� 0 ����
	�ǳ��� ���ظ� �޾� �����ߴٸ� 1 ����
	�������� �ʴ� ����� ���ظ� �޾� �����ߴٸ� -1 ����
	Tet->arTet[i] �� 20���� ū ���� �������� �ʴ� ����� �ǹ�
	20���� ���� ���� �����̴� ����� �ǹ�
	0 �� ����� ������ �ǹ�
	
	Tet->Moving[4] �迭�� ���� �����̴� ����� ��ǥ�� �����ϰ� �ִ�.
	*/
	int i;
	int j = 0;

	switch( nDirection )
	{
	case VK_UP:
		break;
	case VK_DOWN:
		for( i = 239 ; i >= 230 ; i-- ) // ���� �Ʒ� ���� �ϳ��� �ִٸ�
		{
			if( 0 < Tet->arTet[i] && Tet->arTet[i] < 20 )
				return -1; // �ƹ��͵� ���� �ʴ´�.
		}
		for( i = 0 ; i < 4 ; i++ ) // �������� �ʴ� ����� ���ظ� �������
		{
			if( Tet->arTet[ Tet->Moving[i] + 10 ] > 20 )
				return -1; // ����
		}

		for( i = 0 ; i < 4 ; i++ )
		{
			Tet->arTet[ Tet->Moving[i] ] = 0; // ��������� 0���� �����
			Tet->Moving[i] += 10;			// �Ʒ��� ��ĭ�� ������
		}
		for( i = 0 ; i < 4 ; i++ )
		{
			Tet->arTet[ Tet->Moving[i] ] = Tet->nCurrentBlockShape; // ��� ����
		}
		Tet->nYpos++;
		return 0;

		break;
	case VK_LEFT:
		for( i = 0 ; i < 240 ; i = i + 10 ) // ���� ���ʿ� ���� �ϳ��� ������
		{
			if( 0 < Tet->arTet[i] && Tet->arTet[i] < 20 )
				return 1; // ����
		}
		for( i = 0 ; i < 4 ; i++ )
		{
			if( Tet->arTet[ Tet->Moving[i] - 1 ] > 20 ) // �������� �ʴ� ��Ͽ� ���� ���ظ� ����
				return -1;
		}

		for( i = 0 ; i < 4 ; i++ ) // �������� ��ĭ�� �̵�
		{
			Tet->arTet[ Tet->Moving[i] ] = 0;
			Tet->Moving[i] -= 1;			
		}
		for( i = 0 ; i < 4 ; i++ )
		{
			Tet->arTet[ Tet->Moving[i] ] = Tet->nCurrentBlockShape;
		}
		Tet->nXpos--;
		return 0;
		break;
	case VK_RIGHT:

		for( i = 9 ; i < 240; i = i + 10 ) // ���� �������� ���ظ� �޾� �������� �������
		{
			if( 0 < Tet->arTet[i] && Tet->arTet[i] < 20 )
				return 1;
		}
		for( i = 0 ; i < 4 ; i++ )
		{
			if( Tet->arTet[ Tet->Moving[i] + 1 ] > 20 ) // �������� �ʴ� ����� ���ظ� ����
				return -1;
		}

		for( i = 0 ; i < 4 ; i++ ) // ���������� ��ĭ�� �̵�
		{
			Tet->arTet[ Tet->Moving[i] ] = 0;
			Tet->Moving[i] += 1;			
		}
		for( i = 0 ; i < 4 ; i++ )
		{
			Tet->arTet[ Tet->Moving[i] ] = Tet->nCurrentBlockShape ;
		}
		Tet->nXpos++;
		return 0;
		break;
	}
	return 0;
}

int MakeSolidBlocks( TETRIS *Tet )
{
	// �������� �ʴ� ������� �ٲ�
	int i;
	int j = 0;
	for( i = 0; i < 240 ; i++ )
	{
		if(0 < Tet->arTet[i] && Tet->arTet[i] < 20 )
		{
			Tet->arTet[i] = Tet->arTet[i] + 20;
			j++;
		}
		if( j == 4 )
			break;
	}
	return j;
}
int MakeTransparentBlocks( TETRIS *Tet )
{
	/*
	�� �Լ��� �����̴� ����� �ٴڿ� ������� ��� ��ġ�ϰ� ���� �����մϴ�
	���� �����̴� ����� blocks �� cpblocks �� �����ѵ�
	����ȭ �Ŀ� �ٴڿ� �̸��� �ּҰ��� nMin �� �־��ݴϴ�.
	nMin ���� ���� Tet->Transparent[4] �迭�� -1 �� �� ��ǥ�� ��������ݴϴ�.
	*/
	int Blocks[4] = { 0 };
	int cpBlocks[4] = { 0 };
	int i = 0;
	int j = 0;
	int k = 0;
	int nMin = 240;
	

	for( i = 0 ; i < 4 ; i++ )
	{
		if( Tet->arTet[ Tet->Transparent[i] ] == -1 )
			Tet->arTet[ Tet->Transparent[i] ] = 0;
	}

	for( i = 0 ; i < 4 ; i++ )
	{
		Blocks[i] = cpBlocks[i] = Tet->Moving[i];
	}

	for( i = 0 ; i < 4 ; i++ ) // ����ȭ
	{	
		for( j = 0 ; j < 4 ; j++ )
		{
			if( i != j && Blocks[i] != -1 && Blocks[j] != -1)
			{
				if( Blocks[j] % 10 == Blocks[i] % 10 )
				{
					if( Blocks[i] > Blocks[j] )
					{
						Blocks[j] = -1;
						j++;
					}
					else
					{
						Blocks[i] = -1;
						i++;
					}
				}
			}
		}
	}

	for( k = 0 ; k < 4 ; k++ ) // ����ȭ�� ����� ����
	{
		if( Blocks[k] != -1 )
		{
			j = 0;
			for( i = Blocks[k] ; i < 240 ; i = i + 10 )
			{		
				if( Tet->arTet[i + 10] > 20 || i >= 230) // ����� �߰ߵǰų� �� �� �ٴ��̰ų�
				{
					if( nMin > j )
					{			
						nMin = j;
						break;
					}
				}
				j++;
			}
		}
	}
	
	for( i = 0 ; i < 4 ; i++ )
	{
		Tet->Transparent[i] = cpBlocks[i] + nMin * 10;
	}
	
	for( i = 0 ; i < 4 ; i++ )
	{
		if( Tet->arTet[ Tet->Transparent[i] ] == 0 )
			Tet->arTet[ Tet->Transparent[i] ] = -1;
	}	

	return nMin;
}

int RotateBlocks( TETRIS *Tet )
{
	TETRIS temp;

	temp = *Tet;// �ӽú����� �����Ѵ�
	if( temp.nCurrentBlockShape == 0 )
		return -1;

	switch( temp.nCurrentBlockShape )
	{
	case OI:
		if( temp.nXpos > 6 )
			temp.nXpos = 6;
		break;
	case LIGHTNING:
	case LIGHTNINGR:
	case NIEUN:
	case NUEUNR:
	case UO:
		if( temp.nXpos > 7 )
			temp.nXpos = 7;		
		break;
	default:
		return -1;
	}

	temp.nCurrentBlockState++;
	switch( temp.nCurrentBlockShape )
	{
	case OI: // ���� ���� �ݴ����
	case LIGHTNING:
	case LIGHTNINGR:
		temp.nCurrentBlockState %= 2;
		break;
	case NIEUN: // ���� �ݴ���� ���
	case NUEUNR:
	case UO:
		temp.nCurrentBlockState %= 4;
		break;
	default: // �׸��ΰ��
		return -1;
		break;
	}
	if( PrePutBlock( &temp ) == FALSE )
	{
		return -1;
	}
	else
	{
		*Tet = temp;
	}
	return 0;
}

void PutBlockInTET( TETRIS *Tet, int nShape) 
{
	// ������ ����� �����ϴ�.
	// �� �Լ��� ȣ��Ǿ�� ��Ʈ�ǿ� ����� �������� ������ ���۵˴ϴ�.
	int i;
	int *ptr;
	int *pShapePtr;

	int pos = 0;
	int ctr = 0;	

	ptr = Tet->arTet;
	ptr = ptr + 4;
	pos = 4;

	Tet->nCurrentBlockShape = nShape;
	Tet->nCurrentBlockState = 0;
	Tet->nXpos = Tet->nXpos + 4;
	Tet->nYpos = 0;
/*
	if( bNewBlock )
	{

	}
	else
	{
		ptr = Tet->arTet;
		ptr = ptr + Tet->nXpos + ( Tet->nYpos * 10 );
	}
*/
	switch( nShape )
	{
	case OI:
		pShapePtr = (int *)Oi;		
		break;		
	case NIEUN:
		pShapePtr = (int *)Nieun;
		break;
	case NUEUNR:
		pShapePtr = (int *)NieunR;
		break;
	case LIGHTNING:
		pShapePtr = (int *)Lightning;
		break;
	case LIGHTNINGR:
		pShapePtr = (int *)LightningR;
		break;
	case UO:
		pShapePtr = (int *)Uo;
		break;
	case NEMO:
		pShapePtr = (int *)Nemo;
		break;
	}
//	pShapePtr = pShapePtr + (16 * Tet->nCurrentBlockState);

	for( i = 1 ; i <= 16 ; i++ )
	{
		if( *pShapePtr != 0 )
		{
			*ptr = *pShapePtr;
			Tet->Moving[ctr++] = pos;
		}

		ptr++;
		pos++;
		pShapePtr++;

		if( i % 4 == 0 )
		{
			ptr = ptr + 6;
			pos += 6;
		}
	}
}

void InitializeTET( TETRIS *Tet )
{
	memset(Tet, 0, sizeof(TETRIS) );
}

BOOL PrePutBlock( TETRIS *Tet )
{
	/* 
	Tet �� ����� ����ü�̹Ƿ� ������� �����ص� �ȴ�.
	�� �Լ��� FALSE �� �����ϰ� �Ǹ� �纻�� ����ϰ� �ȴ�.
	*/
	int i;
	int *ptr;
	int *pShapePtr;

	int pos = 0;
	int ctr = 0;

	ptr = Tet->arTet;
	ptr = ptr + Tet->nXpos + ( Tet->nYpos * 10 );
	pos = Tet->nXpos + Tet->nYpos * 10;

	switch( Tet->nCurrentBlockShape )
	{
	case OI:
		pShapePtr = (int *)Oi;		
		break;		
	case NIEUN:
		pShapePtr = (int *)Nieun;
		break;
	case NUEUNR:
		pShapePtr = (int *)NieunR;
		break;
	case LIGHTNING:
		pShapePtr = (int *)Lightning;
		break;
	case LIGHTNINGR:
		pShapePtr = (int *)LightningR;
		break;
	case UO:
		pShapePtr = (int *)Uo;
		break;
	case NEMO:
		pShapePtr = (int *)Nemo;
		break;
	}
	pShapePtr = pShapePtr + (16 * Tet->nCurrentBlockState); // ���� ������ �����ġ�� ������ �̵�

	for( i = 0 ; i < 4 ; i++ )
	{
		Tet->arTet[ Tet->Moving[i] ] = 0; // �����̴� ��� 0 �ʱ�ȭ
	}

	for( i = 1 ; i <= 16 ; i++ )
	{
		if( *pShapePtr != 0 )
		{
			if( *ptr > 20 )
			{
				return FALSE; // ����� ���� �ڸ��� �ٸ� ����� ������ ����
			}
			else
			{
				*ptr = *pShapePtr;
				Tet->Moving[ctr++] = pos;
			}
		}
		ptr++;
		pos++;
		pShapePtr++;

		if( i % 4 == 0 )
		{
			ptr += 6;
			pos += 6;
		}
	}
	
	return TRUE; // ����� ����� �������ٸ� TRUE
}
void MakeBlockOrder( int *arBckOrder )
{
	int i;
	
	for( i = 0 ; i < MAX_NUM_OF_BLOCK_ORDER ; i++ )
	{
		arBckOrder[i] = rand() % 6 + 1;
	}
}

void ScoreBoard( TETRIS *Tet )
{
	/*
	���ھ� ���� �Լ���..
	������ �� �迭��ҿ� �־��ִ� �Լ��Դϴ�.
	�߰��� 3�ڸ������� �޸��� �ش��ϴ� ���� �Ҵ��� �� �ֽ��ϴ�.
	*/
	int temp;
	int i, j, k;
	int tempScore = Tet->nScore;

	for( i = 0 ; i < 10 ; i++ ) // �� �ڸ����� �迭��� �ϳ��� �ֽ��ϴ�/
	{
		Tet->arScore[i] = tempScore % 10;
		tempScore = tempScore - tempScore % 10;
		tempScore /= 10;
	}

	j = 0; 
	for( i = 0 ; i < 10 ; i++ ) // �� �ڸ������� ���ϴ�.
	{
		if( Tet->arScore[i] != 0 )
			j++;
	}
/*
	k = 0;
	for( i = 3 ; i < 10 ; i += 3 ) //�޸��� �߰���Ű�� ��ƾ�Դϴ�.
	{
		if( Tet->arScore[i + k] != 0 )
		{
			memcpy( &Tet->arScore[i + k + 1], &Tet->arScore[i + k], sizeof(int) * (j - 3 * (k + 1) ) );
			Tet->arScore[i + k] = 10; // �޸��ڸ��� 10�� �ֽ��ϴ�.
			k++;
		}
		else
		{
			break;
		}
	}
*/
	i = 0;
	j = 9;
	while( 1 ) // �迭�� ������ŵ�ϴ�.
	{
		if( i == j || j < i )
			break;

		temp = Tet->arScore[i];
		Tet->arScore[i] = Tet->arScore[j];
		Tet->arScore[j] = temp;
		i++;
		j--;
	}
}