long stats::getSum(char channel, pair<int, int> ul, int dim) {
    long rowSum;
    long sumRight;
    long sumLeft;
    long sum;
    
    int squareLength = pow(2, dim);
    int x = ul.first;
    int y = ul.second;
    int vectorWidth = sumRed.size();

    //x == 0 && y == 0
    //sumRight = sumRed[x + squareLength - 1][y]
    //sumLeft = 0

    //x == 0 && y != 0
    //sumRight = sumRed[x + squareLength - 1][y]
    //sumLeft = sumRed[vectorWidth - 1][y - 1]
    
    //x != 0 && y == 0
    //sumRight = sumRed[x + squareLength - 1][y]
    //sumLeft = sumRed[x - 1][y]

    //x != 0 && y != 0
    //sumRight = sumRed[x + squareLength - 1][y]
    //sumLeft = sumRed[x - 1][y]

if (channel == 'r') {
    for (int i = y; i <= y + squareLength - 1; i++) {

    sumRight = sumRed[x + squareLength - 1][i];

    if (x == 0 && i == 0) {
        sumLeft = 0;
    } else if (x == 0 && i != 0) {
        sumLeft = sumRed[vectorWidth - 1][i - 1];
    } else {
        sumLeft = sumRed[x - 1][i];
    }

    rowSum = sumRight - sumLeft;
    sum += rowSum;

    }

    return sum;
}

if (channel == 'g') {
    for (int i = y; i <= y + squareLength - 1; i++) {

    sumRight = sumGreen[x + squareLength - 1][i];

    if (x == 0 && i == 0) {
        sumLeft = 0;
    } else if (x == 0 && i != 0) {
        sumLeft = sumGreen[vectorWidth - 1][i - 1];
    } else {
        sumLeft = sumGreen[x - 1][i];
    }

    rowSum = sumRight - sumLeft;
    sum += rowSum;

    }

    return sum;
}

if (channel == 'b') {
    for (int i = y; i <= y + squareLength - 1; i++) {

    sumRight = sumBlue[x + squareLength - 1][i];

    if (x == 0 && i == 0) {
        sumLeft = 0;
    } else if (x == 0 && i != 0) {
        sumLeft = sumBlue[vectorWidth - 1][i - 1];
    } else {
        sumLeft = sumBlue[x - 1][i];
    }
    rowSum = sumRight - sumLeft;
    sum += rowSum;
    }

    return sum;
}

return 0;



}