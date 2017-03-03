#include <string.h>
#include "main.h"

/*
short heights[ColMax];
short widths[RowMax];

void CheckStrobe(unsigned int strobePtr, short strobeWidth, short strobeHeight, short minWidth,
       short minHeight, short maxWidth, short maxHeight, unsigned int ethPtr)
{
       short ethLeft = 0;
       short ethTop = 0;
       short ethWidth = strobeWidth;
       short ethHeight = strobeHeight;
       short startWidth = ethWidth;
       short startHeight = ethHeight;
       float startRatio = (float) ethHeight / (float) ethWidth;

       int i, j, k;
       int dx = 0;
       short done = 0;
       short b_left = 0, b_right = 0, b_top = 0, b_bottom = 0;
       short L_Object = 0, R_Object = 0, T_Object = 0, B_Object = 0;

       memset(heights, 0, strobeWidth * 2);
       memset(widths, 0, strobeHeight * 2);

       short top = 0, bottom = 0;
       short topHeight = 0;
       short topWidth = 0;
       Uint32 averageHeight = 0;
       Uint32 averageWidth = 0;

       Uint8 * buffer = (Uint8 *) strobePtr;
       k = 0;
       // подсчитываем высоту объекта в каждом столбце
       for(i = 0; i < strobeWidth; i++){
             for(j = 0; j < strobeHeight; j++){
                    if ( *(buffer + j * strobeWidth + i) != 0 ){
                           if( top == 0 ) top = j;
                           bottom = j;
                    }
             }
             heights[i] = bottom - top;
             if(heights[i] > 0){
                    if(heights[i] > topHeight) {
                           topHeight = heights[i];
                    }

                    averageHeight += heights[i];
                    k++;
             }
             top = 0; bottom = 0;
       }
       //averageHeight /= k;

       float minThickness = ( (float) averageHeight / k + topHeight ) / 8.0;
       float maxThickness = minThickness * 1.1;
       maxThickness = maxThickness - minThickness > 2.0 ? maxThickness : minThickness + 2.0;

       top = 0; bottom = 0;
       k = 0;
       // подсчитываем ширину объекта в каждой строке
       for(i = 0; i < strobeHeight; i++){
             for(j = 0; j < strobeWidth; j++){
                    if ( *(buffer + i * strobeWidth + j) != 0 ){
                           if( top == 0 ) top = j;
                           bottom = j;
                    }
             }
             widths[i] = bottom - top;
             if(widths[i] > 0){
                    if(widths[i] > topWidth) {
                           topWidth = widths[i];
                    }

                    averageWidth += widths[i];
                    k++;
             }
             top = 0; bottom = 0;
       }
       //averageWidth /= k;

       float minWideness = ( (float) averageWidth / k + topWidth ) / 14.0;
       float maxWideness = minWideness * 1.1;
       maxWideness = maxWideness - minWideness > 4.0 ? maxWideness : minWideness + 4.0;

       i = 0;
       // выполняем обход строба слева направо
       while(!done){
             for(j = 0; j < strobeHeight; j++){
                    if( *(buffer + j * strobeWidth + i) ){
                           dx++;
                         if(dx > minThickness || heights[i] > maxThickness){
                          // if(dx > minThickness ){
                                  done = 1;
                           }
                          if(dx > maxThickness || heights[i] > maxThickness + 2){
                           //if(dx > maxThickness){
                                  L_Object = 1;
                           }
                    }
             }

             if(!done){
                    b_left ++;
                    i++;
                    dx = 0;

                    if(i >= strobeWidth){
                           done = 1;
                    }
             }
       }

       if(b_left) L_Object = 0;

       dx = 0;
       i = strobeWidth - 1;

       done = 0;

       // выполняем обход строба справа налево
       while(!done){
             for(j = 0; j < strobeHeight; j++){
                    if( *(buffer + j * strobeWidth + i) ){
                           dx++;
                           if(dx > minThickness || heights[i] > maxThickness){
                            //   if(dx > minThickness){
                                  done = 1;
                           }
                           if(dx > maxThickness || heights[i] > maxThickness + 2){
                          //     if(dx > maxThickness){
                                  R_Object = 1;
                           }
                    }
             }

             if(!done){
                    b_right ++;
                    i--;

                    dx = 0;

                    if(i < 0){
                           done = 1;
                    }
             }
       }

       if(b_right) R_Object = 0;

       dx = 0;
       i = 0;

       done = 0;

       // выполняем обход строба сверху вниз
       while(!done){
             for(j = 0; j < strobeWidth; j++){
                    if( *(buffer + i * strobeWidth + j) ){
                           dx++;

                           if(dx > minWideness || widths[i] > maxWideness){
                         //      if(dx > minWideness){
                                  done = 1;
                           }

                           if(dx > maxWideness || widths[i] > maxWideness){
                      //         if(dx > maxWideness){
                                  T_Object = 1;
                           }
                    }
             }

             if(!done){
                    b_top ++;
                    i++;

                    dx = 0;

                    if(i >= strobeHeight){
                           done = 1;
                    }
             }
       }

       if(b_top) T_Object = 0;

       dx = 0;
       i = strobeHeight - 1;

       done = 0;

       // выполняем обход строба снизу вверх
       while(!done){
             for(j = 0; j < strobeWidth; j++){
                    if( *(buffer + i * strobeWidth + j) ){
                           dx++;

                           if(dx > minWideness || widths[i] > maxWideness){
     //                          if(dx > minWideness){
                                  done = 1;
                           }

                           if(dx > maxWideness || widths[i] > maxWideness){
              //                 if(dx > maxWideness){
                                  B_Object = 1;
                           }
                    }
             }

             if(!done){
                    b_bottom ++;
                    i--;

                    dx = 0;

                    if(i < 0){
                           done = 1;
                    }
             }
       }

       if(b_bottom) B_Object = 0;

       int maxIterations = (b_top + b_right + b_left + b_bottom) << 1;
       i = 0;
       done = 0;

       float curRatio, ratioDiff, lengthDiff, heightDiff;
       float lRatioMin = 0.75;
       float lRatioMax = 1.25;
       float rectRatioMin = 0.15;
       float rectRatioMax = 1.5;
       // Выполняем пошаговую корректировку строба
       while(!done){
             curRatio = (float) ethHeight / (float) ethWidth;
             ratioDiff = startRatio / curRatio;
             lengthDiff = (float) startWidth / (float) ethWidth;
             heightDiff = (float) startHeight / (float) ethHeight;

             // слева - объект
             if( (L_Object) && (ethWidth < maxWidth - 2) && (curRatio > rectRatioMin) ){
                    ethLeft -= 3;
                    ethWidth += 3;
                    L_Object = 0;
             }

             // слева - пустые столбцы
             if( (b_left > 3) && (ethWidth > minWidth) && (lengthDiff > lRatioMin) &&
                    (lengthDiff < lRatioMax) && (ratioDiff < lRatioMax) && (ratioDiff > lRatioMin) &&
                    (curRatio < rectRatioMax) ){
                    ethLeft ++;
                    ethWidth --;
                    b_left --;
             }

             // сверху - объект
             if( (T_Object) && (ethHeight < maxHeight - 2) && (curRatio < rectRatioMax) ){
                    ethHeight += 3;
                    ethTop -= 3;
                    T_Object = 0;
             }

             // сверху - пустые строки
             if( (b_top > 4) && (ethHeight > minHeight) && (heightDiff > lRatioMin) &&
                    (heightDiff < lRatioMax) && (ratioDiff < lRatioMax) && (ratioDiff > lRatioMin) &&
                    (curRatio > rectRatioMin) ){
                    ethTop ++;
                    b_top --;
                    ethHeight --;
             }

             // справа - объект
             if( (R_Object) && ( ethWidth < maxWidth - 2 ) && (curRatio > rectRatioMin) ){
                    ethWidth += 3;
                    R_Object = 0;
             }

             // справа - пустые столбцы
             if( (b_right > 3) && (ethWidth > minWidth) && (lengthDiff > lRatioMin) &&
                    (lengthDiff < lRatioMax) && (ratioDiff < lRatioMax) && (ratioDiff > lRatioMin) &&
                    (curRatio < rectRatioMax) ){
                    ethWidth --;
                    b_right --;
             }

             // снизу - объект
             if( (B_Object) && ( ethHeight < maxHeight - 2 ) && (curRatio < rectRatioMax) ){
                    ethHeight += 3;
                    B_Object = 0;
             }

             // снизу - пустые строки
             if( (b_bottom > 4) && (ethHeight > minHeight) && (heightDiff > lRatioMin) &&
                    (heightDiff < lRatioMax) && (ratioDiff < lRatioMax) && (ratioDiff > lRatioMin) &&
                    (curRatio > rectRatioMin) ){
                    b_bottom --;
                    ethHeight --;
             }

             i++;
             if( i > maxIterations ){
                    done = 1;
             }
       }

       *((short*)ethPtr) = ethLeft;
       *((short*)ethPtr + 1) = ethTop;
       *((short*)ethPtr + 2) = ethWidth;
       *((short*)ethPtr + 3) = ethHeight;
}*/
/*

void CheckStrobe (unsigned int strobePtr, short strobeWidth, short strobeHeight, short minWidth,
       short minHeight, short maxWidth, short maxHeight, unsigned int ethPtr)
{
       const short minThickness = 3;
       const short maxThickness = 5;

       short ethLeft = 0;
       short ethTop = 0;
       short ethWidth = strobeWidth;
       short ethHeight = strobeHeight;

       int i, j;
       int dx = 0;
       short done = 0;
       short l_transactions = 0, r_transactions = 0;
       short b_left = 0, b_right = 0, b_top = 0, b_bottom = 0;
       short L_Object = 0, R_Object = 0, T_Object = 0, B_Object = 0;

       Uint8 * buffer = (Uint8 *) strobePtr;

       // подсчитываем число переходов от фона к контуру и обратно на левом и правом краях
       for(j = 1; j < strobeHeight; j++){
             if( *(buffer + (j - 1) * strobeWidth) != *(buffer + (j) * strobeWidth) ){
                    l_transactions++;
             }

             if( *(buffer + (j - 1) * strobeWidth + strobeWidth - 1) != *(buffer + (j) * strobeWidth + strobeWidth - 1) ){
                    r_transactions++;
             }
       }

       i = 0;
       // выполняем обход строба слева направо
       while(!done){
             for(j = 0; j < strobeHeight; j++){
                    if( *(buffer + j * strobeWidth + i) ){
                           dx++;
                           if(dx > minThickness){
                                  done = 1;
                           }
                           if(dx > maxThickness){
                                  L_Object = 1;
                           }
                    }
             }

             if(!done){
                    b_left ++;
                    i++;
                    dx = 0;

                    if(i >= strobeWidth){
                           done = 1;
                    }
             }
       }

       if(b_left) L_Object = 0;

       dx = 0;
       i = strobeWidth - 1;

       done = 0;

       // выполняем обход строба справа налево
       while(!done){
             for(j = 0; j < strobeHeight; j++){
                    if( *(buffer + j * strobeWidth + i) ){
                           dx++;
                           if(dx > minThickness){
                                  done = 1;
                           }
                           if(dx > maxThickness){
                                  R_Object = 1;
                           }
                    }
             }

             if(!done){
                    b_right ++;
                    i--;

                    dx = 0;

                    if(i < 0){
                           done = 1;
                    }
             }
       }

       if(b_right) R_Object = 0;

       dx = 0;
       i = 0;

       done = 0;

       // выполняем обход строба сверху вниз
       while(!done){
             for(j = 0; j < strobeWidth; j++){
                    if( *(buffer + i * strobeWidth + j) ){
                           dx++;

                           if(dx > minThickness){
                                  done = 1;
                           }

                           if(dx > maxThickness){
                                  T_Object = 1;
                           }
                    }
             }

             if(!done){
                    b_top ++;
                    i++;

                    dx = 0;

                    if(i >= strobeHeight){
                           done = 1;
                    }
             }
       }

       if(b_top) T_Object = 0;

       dx = 0;
       i = strobeHeight - 1;

       done = 0;

       // выполняем обход строба снизу вверх
       while(!done){
             for(j = 0; j < strobeWidth; j++){
                    if( *(buffer + i * strobeWidth + j) ){
                           dx++;

                           if(dx > minThickness){
                                  done = 1;
                           }

                           if(dx > maxThickness){
                                  B_Object = 1;
                           }
                    }
             }

             if(!done){
                    b_bottom ++;
                    i--;

                    dx = 0;

                    if(i < 0){
                           done = 1;
                    }
             }
       }

       if(b_bottom) B_Object = 0;

       int maxIterations = (b_top + b_right + b_left + b_bottom);
       i = 0;
       done = 0;

       // Выполняем пошаговую корректировку строба
       while(!done){

             // слева - объект
             if(L_Object){
                    if( l_transactions == 4 ){
                           if(ethWidth > 2*minWidth){
                                  ethLeft ++;
                                  ethWidth --;
                           }
                    }
                    else if( ethWidth < maxWidth - 1 ){
                           ethLeft -= 2;
                           ethWidth += 2;
                    }
                    L_Object = 0;
             }

             // слева - пустые столбцы
             if( (b_left > 1) && (ethWidth > minWidth) ){
                    ethLeft ++;
                    ethWidth --;
                    b_left --;
             }

             // сверху - объект
             if( (T_Object) && (ethHeight < maxHeight - 1) ){
                    ethHeight += 2;
                    ethTop -= 2;
                    T_Object = 0;
             }

             // сверху - пустые строки
             if( (b_top > 1) && (ethHeight > minHeight) ){
                    ethTop ++;
                    b_top --;
                    ethHeight --;
             }

             // справа - объект
             if(R_Object){
                    if( r_transactions == 4 ){
                           if(ethWidth > 2*minWidth){
                                  ethWidth --;
                           }
                    }
                    else if( ethWidth < maxWidth - 1 ){
                           ethWidth += 2;
                    }
                    R_Object = 0;
             }

             // справа - пустые столбцы
             if( (b_right > 1) && (ethWidth > minWidth) ){
                    ethWidth --;
                    b_right --;
             }

             // снизу - объект
             if(B_Object && (ethHeight < maxHeight - 1) ){
                    ethHeight += 2;
                    B_Object = 0;
             }

             // снизу - пустые строки
             if( (b_bottom > 1) && (ethHeight > minHeight) ){
                    b_bottom --;
                    ethHeight --;
             }

             i++;
             if( i > maxIterations ){
                    done = 1;
             }
       }

       *((short*)ethPtr) = ethLeft;
       *((short*)ethPtr + 1) = ethTop;
       *((short*)ethPtr + 2) = ethWidth;
       *((short*)ethPtr + 3) = ethHeight;
}
*/

Uint16 heights[ColMax];
Uint16 widths[RowMax];

void CheckStrobe(unsigned int strobePtr, short strobeWidth, short strobeHeight, short minWidth,
	short minHeight, short maxWidth, short maxHeight, unsigned int result)
{
	Uint16* rez = (Uint16*) result;
	Uint16 icurrent;

	int temp = 0;
	int signum;
	int smx = rez[0];		// смещение эталона в стробе
	int smy = rez[1];
	Uint16 colsEt = rez[2]; // ширина и высота эталона
	Uint16 rowsEt = rez[3];

	Uint32 startCols = colsEt;
	Uint32 startRows = rowsEt;

	// соотношение сторон прямоугольника эталона
	float startRatio = (float) rowsEt / (float) colsEt;

	Uint32 i, j, k;
	Uint32 dx = 0;

	Uint32 done = 0;
	Uint32 b_left = 0, b_right = 0, b_top = 0, b_bottom = 0;
	Uint32 L_Object = 0, R_Object = 0, T_Object = 0, B_Object = 0;

	Uint32 top = 0, bottom = 0;
	Uint32 topHeight = 0;
	Uint32 topWidth = 0;
	float averageHeight = 0.0;
	float averageWidth = 0.0;

	float curRatio, ratioDiff, lengthDiff, heightDiff;
	float lRatioMin = 0.75;
	float lRatioMax = 1.25;
	float rectRatioMin = 0.15;
	float rectRatioMax = 1.5;

	Uint8* buffer = (Uint8 *) strobePtr;

	// определяем высоту объекта, обходя строб по столбцам
	for(i = 0, k = 0; i < colsEt; i++){
		icurrent = smy * strobeWidth + smx + i;
		for(j = 0; j < rowsEt; j++, icurrent += strobeWidth){
			if(buffer[icurrent] != 0){
				if(top == 0) top = j;
				bottom = j;
			}
		}

		if(temp != 0){
			signum = bottom - top - temp;
			heights[i] = temp + ( ( 3 * signum ) >> 2);
		} else{
			heights[i] = bottom - top;
		}

		if(heights[i] != 0){
			if(heights[i] > topHeight) {
				topHeight = heights[i];
			}

			averageHeight += heights[i];
			k++;
		}
		top = 0; bottom = 0;
	}

	if(k == 0) k = 1;
	averageHeight /= k;

	// вычисляем критерий минимальной высоты
	float minThickness = ( averageHeight )/5.0;//+ topHeight ) / 6.0;

	float maxThickness = minThickness * 1.1;
	maxThickness = maxThickness - minThickness > 3.0 ? maxThickness : minThickness + 3.0;

	top = 0; bottom = 0;

	icurrent = smy * strobeWidth + smx;

	// определяем ширину объекта, обходя строб по строкам
	for(i = 0, k = 0; i < rowsEt; i++, icurrent += strobeWidth){
		for(j = 0; j < colsEt; j++){
			if(buffer[icurrent + j] != 0){
				if(top == 0) top = j;
				bottom = j;
			}
		}

		//temp = (int) widths[i];
		if(temp != 0){
			signum = bottom - top - temp;
			widths[i] = temp + ( ( 3 * signum ) >> 2);
		} else {
			widths[i] = bottom - top;
		}

		if(widths[i] != 0){
			if(widths[i] > topWidth) {
				topWidth = widths[i];
			}

			averageWidth += widths[i];
			k++;
		}
		top = 0; bottom = 0;
	}

	if(k == 0) k = 1;
	averageWidth /= k;

	// вычисляем критерий минимальной ширины
	float minWideness = ( averageWidth )/ 12.0;// + topWidth ) / 14.0;

	float maxWideness = minWideness * 1.1;
	maxWideness = maxWideness - minWideness > 3.0 ? maxWideness : minWideness + 3.0;

	i = 0;
	icurrent = smy * strobeWidth + smx;
	// выполняем обход строба слева направо
	while(done == 0){
		for(j = 0; j < rowsEt; j++, icurrent += strobeWidth){
			if( buffer[icurrent + i] != 0 ){
				dx++;
				if(dx > minThickness || heights[i] > minThickness){
					done = 1;
				}
				if(dx > maxThickness || heights[i] > maxThickness){
					L_Object = 1;
				}
			}
		}

		if(done == 0){
			b_left ++;
			i++;
			icurrent = smy * strobeWidth + smx;
			dx = 0;

			if(i >= colsEt){
				done = 1;
			}
		}
	}

	if(b_left != 0) L_Object = 0;

	dx = 0;
	i = colsEt - 1;
	icurrent = smy * strobeWidth + smx;

	done = 0;

	// выполняем обход строба справа налево
	while(done == 0){
		for(j = 0; j < rowsEt; j++, icurrent += strobeWidth){
			if( buffer[icurrent + i] != 0 ){
				dx++;
				if(dx > minThickness || heights[i] > minThickness){
					done = 1;
				}
				if(dx > maxThickness || heights[i] > maxThickness){
					R_Object = 1;
				}
			}
		}

		if(done == 0){
			b_right ++;
			i--;
			icurrent = smy * strobeWidth + smx;
			dx = 0;

			if(i <= 0){
				done = 1;
			}
		}
	}

	if(b_right != 0) R_Object = 0;

	dx = 0;
	i = 0;
	icurrent = (smy + i) * strobeWidth + smx;
	done = 0;

	// выполняем обход строба сверху вниз
	while(done == 0){
		for(j = 0; j < colsEt; j++){
			if( buffer[icurrent + j] != 0 ){
				dx++;

				if(dx > minWideness || widths[i] > minWideness){
					done = 1;
				}

				if(dx > maxWideness || widths[i] > maxWideness){
					T_Object = 1;
				}
			}
		}

		if(done == 0){
			b_top ++;
			i++;
			icurrent += strobeWidth;
			dx = 0;

			if(i >= rowsEt){
				done = 1;
			}
		}
	}

	if(b_top != 0) T_Object = 0;

	dx = 0;
	i = rowsEt - 1;
	icurrent = (smy + i) * strobeWidth + smx;
	done = 0;

	// выполняем обход строба снизу вверх
	while(done == 0){
		for(j = 0; j < colsEt; j++){
			if( buffer[icurrent + j] != 0 ){
				dx++;

				if(dx > minWideness || widths[i] > minWideness){
					done = 1;
				}

				if(dx > maxWideness || widths[i] > maxWideness){
					B_Object = 1;
				}
			}
		}

		if(done == 0){
			b_bottom ++;
			i--;
			icurrent -= strobeWidth;
			dx = 0;

			if(i <= 0){
				done = 1;
			}
		}
	}

	if(b_bottom != 0) B_Object = 0;

	Uint32 maxIterations = (b_top + b_right + b_left + b_bottom);
	i = 0;
	done = 0;

	// Выполняем пошаговую корректировку строба
	while(done == 0){
		curRatio = (float) rowsEt / (float) colsEt;
		ratioDiff = startRatio / curRatio;
		lengthDiff = (float) startCols / (float) colsEt;
		heightDiff = (float) startRows / (float) rowsEt;

		done = 1;

		// слева - объект
		if( (L_Object != 0) && (colsEt < maxWidth - 3) && (curRatio > rectRatioMin) ){
			smx -= 3;
			colsEt += 3;
			L_Object = 0;
			done = 0;
		}

		// слева - пустые столбцы
		if( (b_left > 5) && (colsEt > minWidth) && (lengthDiff > lRatioMin) &&
			(lengthDiff < lRatioMax) && (ratioDiff < lRatioMax) && (ratioDiff > lRatioMin) &&
			(curRatio < rectRatioMax) && (b_left >= b_right) ){
			smx ++;
			colsEt --;
			b_left --;
			done = 0;
		}

		// сверху - объект
		if( (T_Object != 0) && (rowsEt < maxHeight - 3) && (curRatio < rectRatioMax) ){
			rowsEt += 3;
			smy -= 3;
			T_Object = 0;
			done = 0;
		}

		// сверху - пустые строки
		if( (b_top > 5) && (rowsEt > minHeight) && (heightDiff > lRatioMin) &&
			(heightDiff < lRatioMax) && (ratioDiff < lRatioMax) && (ratioDiff > lRatioMin) &&
			(curRatio > rectRatioMin) && (b_top >= b_bottom) ){
			smy ++;
			b_top --;
			rowsEt --;
			done = 0;
		}

		// справа - объект
		if( (R_Object != 0) && ( colsEt < maxWidth - 3 ) && (curRatio > rectRatioMin) ){
			colsEt += 3;
			R_Object = 0;
			done = 0;
		}

		// справа - пустые столбцы
		if( (b_right > 5) && (colsEt > minWidth) && (lengthDiff > lRatioMin) &&
			(lengthDiff < lRatioMax) && (ratioDiff < lRatioMax) && (ratioDiff > lRatioMin) &&
			(curRatio < rectRatioMax) && (b_right >= b_left) ){
			colsEt --;
			b_right --;
			done = 0;
		}

		// снизу - объект
		if( (B_Object != 0) && ( rowsEt < maxHeight - 3 ) && (curRatio < rectRatioMax) ){
			rowsEt += 3;
			B_Object = 0;
			done = 0;
		}

		// снизу - пустые строки
		if( (b_bottom > 5) && (rowsEt > minHeight) && (heightDiff > lRatioMin) &&
			(heightDiff < lRatioMax) && (ratioDiff < lRatioMax) && (ratioDiff > lRatioMin) &&
			(curRatio > rectRatioMin) && (b_bottom >= b_top) ){
			b_bottom --;
			rowsEt --;
			done = 0;
		}

		i++;
		if( i > maxIterations ){
			done = 1;
		}
	}

	rez[0] = (short) smx;
	rez[1] = (short) smy;
	rez[2] = (short) colsEt;
	rez[3] = (short) rowsEt;
}

/*void CheckStrobe (unsigned int strobePtr, short strobeWidth, short strobeHeight, short minWidth,
       short minHeight, short maxWidth, short maxHeight, unsigned int ethPtr)
{
       const short minThickness = 3;
       const short maxThickness = 5;

       short ethLeft = 0;
       short ethTop = 0;
       short ethWidth = strobeWidth;
       short ethHeight = strobeHeight;

       short startWidth = ethWidth;
       short startHeight = ethHeight;
       float startRatio = (float) ethHeight / (float) ethWidth;

       int i, j;
       int dx = 0;
       short done = 0;
       short l_transactions = 0, r_transactions = 0;
       short b_left = 0, b_right = 0, b_top = 0, b_bottom = 0;
       short L_Object = 0, R_Object = 0, T_Object = 0, B_Object = 0;

       Uint8 * buffer = (Uint8 *) strobePtr;

       // подсчитываем число переходов от фона к контуру и обратно на левом и правом краях
       for(j = 1; j < strobeHeight; j++){
             if( *(buffer + (j - 1) * strobeWidth) != *(buffer + (j) * strobeWidth) ){
                    l_transactions++;
             }

             if( *(buffer + (j - 1) * strobeWidth + strobeWidth - 1) != *(buffer + (j) * strobeWidth + strobeWidth - 1) ){
                    r_transactions++;
             }
       }

       i = 0;
       // выполняем обход строба слева направо
       while(!done){
             for(j = 0; j < strobeHeight; j++){
                    if( *(buffer + j * strobeWidth + i) ){
                           dx++;
                           if(dx > minThickness){
                                  done = 1;
                           }
                           if(dx > maxThickness){
                                  L_Object = 1;
                           }
                    }
             }

             if(!done){
                    b_left ++;
                    i++;
                    dx = 0;

                    if(i >= strobeWidth){
                           done = 1;
                    }
             }
       }

       if(b_left) L_Object = 0;

       dx = 0;
       i = strobeWidth - 1;

       done = 0;

       // выполняем обход строба справа налево
       while(!done){
             for(j = 0; j < strobeHeight; j++){
                    if( *(buffer + j * strobeWidth + i) ){
                           dx++;
                           if(dx > minThickness){
                                  done = 1;
                           }
                           if(dx > maxThickness){
                                  R_Object = 1;
                           }
                    }
             }

             if(!done){
                    b_right ++;
                    i--;

                    dx = 0;

                    if(i < 0){
                           done = 1;
                    }
             }
       }

       if(b_right) R_Object = 0;

       dx = 0;
       i = 0;

       done = 0;

       // выполняем обход строба сверху вниз
       while(!done){
             for(j = 0; j < strobeWidth; j++){
                    if( *(buffer + i * strobeWidth + j) ){
                           dx++;

                           if(dx > minThickness){
                                  done = 1;
                           }

                           if(dx > maxThickness){
                                  T_Object = 1;
                           }
                    }
             }

             if(!done){
                    b_top ++;
                    i++;

                    dx = 0;

                    if(i >= strobeHeight){
                           done = 1;
                    }
             }
       }

       if(b_top) T_Object = 0;

       dx = 0;
       i = strobeHeight - 1;

       done = 0;

       // выполняем обход строба снизу вверх
       while(!done){
             for(j = 0; j < strobeWidth; j++){
                    if( *(buffer + i * strobeWidth + j) ){
                           dx++;

                           if(dx > minThickness){
                                  done = 1;
                           }

                           if(dx > maxThickness){
                                  B_Object = 1;
                           }
                    }
             }

             if(!done){
                    b_bottom ++;
                    i--;

                    dx = 0;

                    if(i < 0){
                           done = 1;
                    }
             }
       }

       if(b_bottom) B_Object = 0;

       int maxIterations = (b_top + b_right + b_left + b_bottom);
              i = 0;
              done = 0;

              float curRatio, ratioDiff, lengthDiff, heightDiff;
              float lRatioMin = 0.75;
              float lRatioMax = 1.25;
              float rectRatioMin = 0.15;
              float rectRatioMax = 1.5;
              // Выполняем пошаговую корректировку строба
              while(!done){
                    curRatio = (float) ethHeight / (float) ethWidth;
                    ratioDiff = startRatio / curRatio;
                    lengthDiff = (float) startWidth / (float) ethWidth;
                    heightDiff = (float) startHeight / (float) ethHeight;

                    // слева - объект
                    if( (L_Object) && (ethWidth < maxWidth - 2) && (curRatio > rectRatioMin) ){
                           ethLeft -= 3;
                           ethWidth += 3;
                           L_Object = 0;
                    }

                    // слева - пустые столбцы
                    if( (b_left > 3) && (ethWidth > minWidth) && (lengthDiff > lRatioMin) &&
                           (lengthDiff < lRatioMax) && (ratioDiff < lRatioMax) && (ratioDiff > lRatioMin) &&
                           (curRatio < rectRatioMax) ){
                           ethLeft ++;
                           ethWidth --;
                           b_left --;
                    }

                    // сверху - объект
                    if( (T_Object) && (ethHeight < maxHeight - 2) && (curRatio < rectRatioMax) ){
                           ethHeight += 3;
                           ethTop -= 3;
                           T_Object = 0;
                    }

                    // сверху - пустые строки
                    if( (b_top > 4) && (ethHeight > minHeight) && (heightDiff > lRatioMin) &&
                           (heightDiff < lRatioMax) && (ratioDiff < lRatioMax) && (ratioDiff > lRatioMin) &&
                           (curRatio > rectRatioMin) ){
                           ethTop ++;
                           b_top --;
                           ethHeight --;
                    }

                    // справа - объект
                    if( (R_Object) && ( ethWidth < maxWidth - 2 ) && (curRatio > rectRatioMin) ){
                           ethWidth += 3;
                           R_Object = 0;
                    }

                    // справа - пустые столбцы
                    if( (b_right > 3) && (ethWidth > minWidth) && (lengthDiff > lRatioMin) &&
                           (lengthDiff < lRatioMax) && (ratioDiff < lRatioMax) && (ratioDiff > lRatioMin) &&
                           (curRatio < rectRatioMax) ){
                           ethWidth --;
                           b_right --;
                    }

                    // снизу - объект
                    if( (B_Object) && ( ethHeight < maxHeight - 2 ) && (curRatio < rectRatioMax) ){
                           ethHeight += 3;
                           B_Object = 0;
                    }

                    // снизу - пустые строки
                    if( (b_bottom > 4) && (ethHeight > minHeight) && (heightDiff > lRatioMin) &&
                           (heightDiff < lRatioMax) && (ratioDiff < lRatioMax) && (ratioDiff > lRatioMin) &&
                           (curRatio > rectRatioMin) ){
                           b_bottom --;
                           ethHeight --;
                    }

                    i++;
                    if( i > maxIterations ){
                           done = 1;
                    }
              }

              *((short*)ethPtr) = ethLeft;
              *((short*)ethPtr + 1) = ethTop;
              *((short*)ethPtr + 2) = ethWidth;
              *((short*)ethPtr + 3) = ethHeight;
}*/

inline Uint32 checkLine(Uint8 * strobPtr, Uint32 stWidth, Uint32 stHeight, float k, float b, Uint32 eth, Uint8 mode, Uint16 lVal, Uint16 rVal){
	volatile Uint32 length = 0;
	int up, down, curHeight, oldHeight;
	Uint16 i, j, n;
	Uint16 shift4 = stWidth;
	Uint16* ethParams = (Uint16*) eth;

	Uint16 smx = ethParams[0];
	//Uint16 smy = ethParams[1];
	Uint16 etWidth = ethParams[2];
	//Uint16 etHeight = ethParams[3];

	volatile Uint8 point, pointUp, pointDown;
	Uint8 * data = strobPtr;
	int done;

	float avg_height, rez;
	volatile float y;

	switch(mode)
	{
		case(0):													// analysis mode
			{
				length = 0;
				for(i = smx; i < smx + etWidth; i++){
					y = k * i + b;
					if(y < (float)stHeight && y >= 0.0){
						point = *(data +  (Uint16) y * shift4 + i);
						//point = data[ ( (Uint16) floor(y) ) * shift4 + i];
						if(y + 1.0 < stHeight){
							//pointUp = data[ ( (Uint16) floor(y + 1) ) * shift4 + i];
							pointUp = *(data + (Uint16) (y + 1) * shift4 + i);
						}
						else {
							pointUp = 0;
						}

						if(y - 1.0 >= 0.0){
							//pointDown = data[ ( (Uint16) floor(y - 1) ) * shift4 + i];
							pointDown = *(data + (Uint16) (y - 1) * shift4 + i);
						}
						else{
							pointDown = 0;
						}

						if(point != 0){
							length++;								// line length
						}
						if(pointUp != 0){
							length++;								// line length
						}
						if(pointDown != 0){
							length++;								// line length
						}
					}
				}
				break;
			}
		case(1):													// horizon removal mode
			{
				length = 0;
				done = 0;
				rez = 0.0;
				avg_height = 0.0;

				for(i = smx, n = 0; i < smx + etWidth; i++){
					done = 0;
					y = k * i + b;

					if( (y >= 0) && (y < stHeight) ){
						up = (y + 1 + 0.5);
						while( (up < stHeight) && (done == 0) ){
							if(data[up * shift4 + i] == 0){
								done = 1;
							}
							up++;
						}

						done = 0;
						if(y - 1 >= 0){
							down = (y - 1 + 0.5);
						}
						else{
							down = 0;
						}

						while( (down >= 0) && (done == 0) ){
							if(data[down * shift4 + i] == 0){
								done = 1;
							}
							down--;
						}

						curHeight = up - down;

						if(n != 0){
							rez = avg_height / n;
						}
						else rez = curHeight;

						if( (curHeight != 0) && (curHeight <= rez + 4) ){
							avg_height += curHeight;
							n++;

							for(j = down; j <= up; j++){
								data[j * shift4 + i] = 0;
							}

							if( (up > stHeight - 64) && (up + 32 < stHeight) ){
								for(j = up + 32; j < stHeight; j++){
									data[j * shift4 + i] = 0;
								}
							}
						}
					}
				}
				break;
			}
		case(2):											// trace removal mode
			{
				if(lVal > rVal){							// right-to-left
					length = 0;
					done = 0;
					curHeight = 0;
					oldHeight = 0;

					for(i = smx + etWidth - 1; i > smx + (etWidth/2.0) - 32; i--){
						done = 0;
						y = k * i + b;

						if( (y >= 0) && (y < stHeight) ){
							up = (y + 1 + 0.5);
							while( (up < stHeight) && (done == 0) ){
								if(data[up * shift4 + i] == 0){
									done = 1;
								}
								up++;
							}

							done = 0;

							if(y - 1 >= 0){
								down = (int) (y - 1 + 0.5);
							}
							else{
								down = 0;
							}

							while( (down >= 0) && (done == 0) ){
								if(data[down * shift4 + i] == 0){
									done = 1;
								}
								down--;
							}

							oldHeight = curHeight;
							curHeight = up - down;

							if( (curHeight <= oldHeight) ){
								for(j = down; j <= up; j++){
									data[j * shift4 + i] = 0;
								}
							}
						}
					}
				}
				else{										// left-to-right

				}
				break;
			}
	}

	return length;
}


const Uint16 zone = 5;

Uint16 horizonFilter(Uint8 * strobPtr, Uint32 stWidth, Uint32 stHeight, Uint32 eth, Uint16 avgH)
{
	Uint8 * buffer = strobPtr;								// strobe ptr
	Uint8 done;												// while cycle stop word
	Uint8 exists;
	Uint16 j1, j2;											// iterators
	Uint16 i1, i2;
	Uint16 l, r;
	Uint16 limR = 0, limL = 0, maxIters = 15;
	Uint16 shift4 = stWidth;
	Uint16* ethParams = (Uint16*) eth;						// short struct pointer

	Uint16 smx = ethParams[0];								// shift along x coordinate
	Uint16 smy = ethParams[1];								// shift along y coordinate
	Uint16 etWidth = ethParams[2];							// strobe width
	Uint16 etHeight = ethParams[3];							// strobe height

	Uint32 ptrShift1, ptrShift2;
	Uint32 length, maxLength = 0;							// line length
	Uint32 stopCriteria1 = etWidth + (etWidth >> 1) + (etWidth >> 2);	// 3l > (7/4)*w
	Uint32 stopCriteria2 = (etWidth << 1) + (etWidth >> 2);				// 3l > (9/4)*w

	//	******************************************************************************************************************
	//  here and everywhere else line length is measured as L = H[y = k*x + b] + H[y = k*x + b + 1] + H[y = k*x + b - 1]
	//  where H(F(x)) is amount of white pixels lying on a line F(x) in [smx; smx + etWidth] bounds
	//  ******************************************************************************************************************
	float k = 0.0, b = 0.0;									// line params
	float bestK = 0.0, bestB = 0.0;

	i1 = smx, i2 = smx + etWidth;
	done = 0;
	exists = 1;

	while(done == 0){
		for(j1 = smy, ptrShift1 = smy * shift4, l = 0; j1 < smy + etHeight; j1++, ptrShift1 += shift4){
			if(buffer[ptrShift1 + i1] != 0){				// iterate over leftmost column's white pixels
				l++;
				for(j2 = smy, ptrShift2 = smy * shift4, r = 0; j2 < smy + etHeight; j2++, ptrShift2 += shift4){
					if(buffer[ptrShift2 + i2] != 0){		// iterate over rightmost column's white pixels
						exists = 1;
						r++;
						if(i1 != i2){						// calculate line params according to equation y = k * x + b;
							b = ( (float) i1 *  (float) j2 -  (float) i2 *  (float) j1) / ( (float) i1 -  (float) i2);

							if(i1 > 0){
								k = ( (float) j1 - b) / (float) i1;
							}
							else if(i2 > 0){
								k = ( (float) j2 - b) / (float) i2;
							}
							else {
								k = 0;
								exists = 0;
							}
						}
						else{
							k = 0;
							b = 0;
							exists = 0;
						}

						if(exists == 1){						// if line exists
							length = checkLine(strobPtr, stWidth, stHeight, k, b, eth, 0, 0, 0);

							if( (k > -0.33) && (k < 0.33) ){	// choose only lines within ~18 degrees angle (+-)
								if(length > maxLength){			// find the best line parameters similar to horizon
									maxLength = length;
									bestK = k;
									bestB = b;
								}
							}
						}
					}
				}

				if( (r < 1) || (maxLength < stopCriteria2) ){	// if there were not much lines, or they found to be bad
					if( (i2 - 18 > i1) && (limR < maxIters) ){
						i2 --;
						limR ++;
					}
				}
				else{
					done = 1;
				}
			}
		}

		if( (l < 1) || (maxLength < stopCriteria2) ){			// same here
			if( (i1 + 18 < i2) && (limL < maxIters) ){
				i1 ++;
				limL++;
				limR = 0;
			}
			else{
				done = 1;
			}
			i2 = smx + etWidth;
		}
		else{
			done = 1;
		}

	}


	float dH;

	if(avgH != 0){
		dH = abs( 1.0 - (bestB / (float) avgH) );
	}
	else dH = 0;

	done = 0;

	if( dH < 0.2 ){								// delete horizon
		if( (maxLength >= stopCriteria1) ){
			checkLine(strobPtr, stWidth, stHeight, bestK, bestB, eth, 1, limL, limR);
			done = 1;
		}
	}

	return (bestB);
}
