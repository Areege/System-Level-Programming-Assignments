// Areege Chaudhary 10197607
// Garett MacGowan 10197107

#include <stdio.h>
#include <stdlib.h>

#define JUDGES 9
#define SCOMPARE 0.6

float getDifficulty() {
  float difficulty;
  printf("Enter the dive's degree of difficulty: ");
  scanf("%f", &difficulty);
  return difficulty;
} //end getDifficulty

float* sortScores(float* scores) {
  int j, i;
  float temp;
  for (i = 0; i < (JUDGES - 1); i++) { 
    for (j = 0; j < ((JUDGES-1) - i); j++) {
      if (scores[j] > scores[j + 1]) {
	temp = scores[j];
	scores[j] = scores[j + 1];
	scores[j + 1] = temp;
      }//end if statement
    }//end for loop
  }//end for loop
  return scores;
}//end sortScores

float * getScores() {
  static float scores[9];
  float y;
  int i;
  for (i = 0; i < 9; i++) {
    printf("Enter score %d: ", (i + 1));
    scanf("%f", &y);
    scores[i] = y;
  }//end for loop
  return scores;
}//end getScores

float calculateScore(float* scores, float difficulty) {
  float sum = 0;
  float finalScore;
  int i;
  for (i = 2; i < 7; i++) {
    sum = sum + scores[i];
  }//end for loop
  finalScore = (sum * difficulty * SCOMPARE);
  return finalScore;
}//end calculateScore

void output(float finalScore, float* scores) {
  #ifdef DEBUG
  printf("low scores are %.1f and %.1f, high scores are %.1f and %.1f\n", scores[0], scores[1], scores[8], scores[7]);
  #endif
  printf("Score for this dive is %.1f\n", finalScore);
}//end output

int main() {
  float finalScore, *scores, difficulty;
  difficulty = getDifficulty();
  scores = getScores();
  scores = sortScores(scores);
  finalScore = calculateScore(scores, difficulty);
  output(finalScore, scores);
  return 0;
} // end main
