#include "stdafx.h"
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
	블록이 제대로 움직였으면 0 리턴
	맨끝의 방해를 받아 실패했다면 1 리턴
	움직이지 않는 블록의 방해를 받아 실패했다면 -1 리턴
	Tet->arTet[i] 의 20보다 큰 값은 움직이지 않는 블록을 의미
	20보다 작은 값은 움직이는 블록을 의미
	0 은 블록이 없음을 의미
	
	Tet->Moving[4] 배열은 현재 움직이는 블록의 좌표를 저장하고 있다.
	*/
	int i;
	int j = 0;

	switch( nDirection )
	{
	case VK_UP:
		break;
	case VK_DOWN:
		for( i = 239 ; i >= 230 ; i-- ) // 가장 아래 블럭이 하나라도 있다면
		{
			if( 0 < Tet->arTet[i] && Tet->arTet[i] < 20 )
				return -1; // 아무것도 하지 않는다.
		}
		for( i = 0 ; i < 4 ; i++ ) // 움직이지 않는 블록의 방해를 받을경우
		{
			if( Tet->arTet[ Tet->Moving[i] + 10 ] > 20 )
				return -1; // 종료
		}

		for( i = 0 ; i < 4 ; i++ )
		{
			Tet->arTet[ Tet->Moving[i] ] = 0; // 원래블록을 0으로 만들고
			Tet->Moving[i] += 10;			// 아래로 한칸씩 내린후
		}
		for( i = 0 ; i < 4 ; i++ )
		{
			Tet->arTet[ Tet->Moving[i] ] = Tet->nCurrentBlockShape; // 블록 갱신
		}
		Tet->nYpos++;
		return 0;

		break;
	case VK_LEFT:
		for( i = 0 ; i < 240 ; i = i + 10 ) // 가장 왼쪽에 블럭이 하나라도 있으면
		{
			if( 0 < Tet->arTet[i] && Tet->arTet[i] < 20 )
				return 1; // 종료
		}
		for( i = 0 ; i < 4 ; i++ )
		{
			if( Tet->arTet[ Tet->Moving[i] - 1 ] > 20 ) // 움직이지 않는 블록에 의해 방해를 받음
				return -1;
		}

		for( i = 0 ; i < 4 ; i++ ) // 왼쪽으로 한칸씩 이동
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

		for( i = 9 ; i < 240; i = i + 10 ) // 가장 오른쪽의 방해를 받아 움직이지 않을경우
		{
			if( 0 < Tet->arTet[i] && Tet->arTet[i] < 20 )
				return 1;
		}
		for( i = 0 ; i < 4 ; i++ )
		{
			if( Tet->arTet[ Tet->Moving[i] + 1 ] > 20 ) // 움직이지 않는 블록의 방해를 받음
				return -1;
		}

		for( i = 0 ; i < 4 ; i++ ) // 오른쪽으로 한칸씩 이동
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
	// 움직이지 않는 블록으로 바꿈
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
	이 함수는 움직이는 블록이 바닥에 닿았을때 어디에 위치하게 될지 예측합니다
	현재 움직이는 블록을 blocks 와 cpblocks 에 복사한뒤
	최적화 후에 바닥에 이르는 최소값을 nMin 에 넣어줍니다.
	nMin 값을 통해 Tet->Transparent[4] 배열에 -1 이 될 좌표를 저장시켜줍니다.
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

	for( i = 0 ; i < 4 ; i++ ) // 최적화
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

	for( k = 0 ; k < 4 ; k++ ) // 최적화된 블록을 통해
	{
		if( Blocks[k] != -1 )
		{
			j = 0;
			for( i = Blocks[k] ; i < 240 ; i = i + 10 )
			{		
				if( Tet->arTet[i + 10] > 20 || i >= 230) // 블록이 발견되거나 맨 밑 바닥이거나
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

	temp = *Tet;// 임시변수에 복사한다
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
	case OI: // 오이 번개 반대번개
	case LIGHTNING:
	case LIGHTNINGR:
		temp.nCurrentBlockState %= 2;
		break;
	case NIEUN: // 니은 반대니은 우오
	case NUEUNR:
	case UO:
		temp.nCurrentBlockState %= 4;
		break;
	default: // 네모인경우
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
	// 지정된 블록을 놓습니다.
	// 이 함수가 호출되어야 테트판에 블록이 놓아지고 게임이 시작됩니다.
	int i;
	int *ptr;
	int *pShapePtr = NULL;

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
	Tet 는 복사된 구조체이므로 마음대로 수정해도 된다.
	이 함수가 FALSE 를 리턴하게 되면 사본을 폐기하게 된다.
	*/
	int i;
	int *ptr;
	int *pShapePtr = NULL;

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
	pShapePtr = pShapePtr + (16 * Tet->nCurrentBlockState); // 현재 상태의 블록위치로 포인터 이동

	for( i = 0 ; i < 4 ; i++ )
	{
		Tet->arTet[ Tet->Moving[i] ] = 0; // 움직이는 블록 0 초기화
	}

	for( i = 1 ; i <= 16 ; i++ )
	{
		if( *pShapePtr != 0 )
		{
			if( *ptr > 20 )
			{
				return FALSE; // 블록을 놓을 자리에 다른 블록이 있으면 실패
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
	
	return TRUE; // 블록이 제대로 놓아졌다면 TRUE
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
	스코어 보드 함수는..
	점수를 각 배열요소에 넣어주는 함수입니다.
	추가로 3자리수마다 콤마에 해당하는 값을 할당할 수 있습니다.
	*/
	int temp;
	int i, j, k;
	int tempScore = Tet->nScore;

	for( i = 0 ; i < 10 ; i++ ) // 각 자리수를 배열요소 하나에 넣습니다/
	{
		Tet->arScore[i] = tempScore % 10;
		tempScore = tempScore - tempScore % 10;
		tempScore /= 10;
	}

	j = 0; 
	for( i = 0 ; i < 10 ; i++ ) // 몇 자리수인지 셉니다.
	{
		if( Tet->arScore[i] != 0 )
			j++;
	}
/*
	k = 0;
	for( i = 3 ; i < 10 ; i += 3 ) //콤마를 추가시키는 루틴입니다.
	{
		if( Tet->arScore[i + k] != 0 )
		{
			memcpy( &Tet->arScore[i + k + 1], &Tet->arScore[i + k], sizeof(int) * (j - 3 * (k + 1) ) );
			Tet->arScore[i + k] = 10; // 콤마자리에 10을 넣습니다.
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
	while( 1 ) // 배열을 반전시킵니다.
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