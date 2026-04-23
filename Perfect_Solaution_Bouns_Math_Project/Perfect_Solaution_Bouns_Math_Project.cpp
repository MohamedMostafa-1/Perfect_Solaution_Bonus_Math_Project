#include <iostream>
#include <cstdlib>

using namespace std;
enum enQuestoinLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OpType;
	enQuestoinLevel QuesLevel;
	int correctAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestoin = 0;
	enQuestoinLevel QuestionLevel ;
	enOperationType Operationtype ;
	short NumberOfRightQuestion = 0;
	short NumberOfWrongQuestion = 0;
	bool isPass = false;
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

//The Reads
short ReadNumberOfQuestions() {
	short  Number = 0;
	do
	{
		cout << "How many you want Questions? ";
		cin >> Number;
	} while (Number < 0);
	return Number;
}
enQuestoinLevel ReadQuestoinLevel() {
	short QLevel = 0;
	do
	{
		cout << "Please Enter Question Level [1]Easy [2]Middle [3]Hard [4]Max : ";
		cin >> QLevel;
	} while (QLevel < 0);
	return (enQuestoinLevel)QLevel;
}
enOperationType ReadOperationType() {
	short OPType = 0;
	do
	{
		cout << "Please Enter Operation Type [1]Add [2]Sub [3]Mult [4]Div [5]Max : ";
		cin >> OPType;
	} while (OPType < 0);
	return (enOperationType)OPType;
}
int ReadAnswer() {
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return (Number2 != 0) ? (Number1 / Number2) : 0;  // Avoid division by zero.
	default:
		return Number1 + Number2;
	}
}

stQuestion GenerateQuestion(enQuestoinLevel QuestoinLevel, enOperationType OpType){
	stQuestion Question;

	if (QuestoinLevel == enQuestoinLevel::Mix)
		QuestoinLevel = (enQuestoinLevel)RandomNumber(1, 3);

	if (OpType == enOperationType::MixOp)
		OpType = (enOperationType)RandomNumber(1, 4);

	Question.OpType = OpType;

	switch (QuestoinLevel)
	{
	case enQuestoinLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		break;
	case enQuestoinLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		break;
	case enQuestoinLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		break;
	}

	Question.correctAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
	Question.QuesLevel = QuestoinLevel;

	return Question;

}

void GenerateQuizzQuestions(stQuizz& Quizz) {
	for (int Question = 0; Question < Quizz.NumberOfQuestoin; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel , Quizz.Operationtype);
	}
}


// ToName
string GetQuestionLevelText(enQuestoinLevel QuestionLevel) {
	string arrQuestionLevelName[4] = { "Easy"   ,"Middle" , "Hard"  , "Max" };
	return arrQuestionLevelName[QuestionLevel - 1];
}
string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}


void PrintQuestion(stQuizz Quizz , short QuestionIndex ) {
	cout << "\nQuestion[" << QuestionIndex+1 << "/" << Quizz.NumberOfQuestoin << "]" << endl;
	cout << Quizz.QuestionList[QuestionIndex].Number1 << endl;
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionIndex].OpType) << endl;
	cout << Quizz.QuestionList[QuestionIndex].Number2 << " ";
	cout << "\n____________________" << endl;

}

void SetColorAnswer(bool AnswerResult){
	if (AnswerResult)
		system("color 2F");
	else
		system("Color 4F");
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionIndex) {
	if (Quizz.QuestionList[QuestionIndex].PlayerAnswer != Quizz.QuestionList[QuestionIndex].correctAnswer) {
		Quizz.QuestionList[QuestionIndex].AnswerResult = false;
		Quizz.NumberOfWrongQuestion++;

		cout << "Wrong Answer :-(" << endl;
		cout << "The Right Answer is : "<< Quizz.QuestionList[QuestionIndex].correctAnswer << endl;
	}
	else
	{
		Quizz.QuestionList[QuestionIndex].AnswerResult = true;
		Quizz.NumberOfRightQuestion++;

		cout << "Right Answer ^_^" << endl;
	}
	SetColorAnswer(Quizz.QuestionList[QuestionIndex].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz ) {
	for (short QuestionIndex = 0; QuestionIndex < Quizz.NumberOfQuestoin; QuestionIndex++)
	{
		PrintQuestion(Quizz, QuestionIndex);
		Quizz.QuestionList[QuestionIndex].PlayerAnswer = ReadAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionIndex);
	}

	Quizz.isPass = (Quizz.NumberOfRightQuestion >= Quizz.NumberOfWrongQuestion);
}

string GetFinalResultText(bool Pass){
	if (Pass)
		return "Pass ^_^";
	else
		return "Fail :-(";
}



void PrintQuizzFinalResult(stQuizz Quizz) {
	cout << "\n_____________________________\n\n";
	cout << "  Final Result is " << GetFinalResultText(Quizz.isPass);
	cout << "\n_____________________________\n\n";
	SetColorAnswer(Quizz.isPass);

	cout << "Number Of Question: " << Quizz.NumberOfQuestoin << endl;
	cout << "Question Level: " << GetQuestionLevelText(Quizz.QuestionLevel)  << endl;
	cout << "Operation Type: " << GetOpTypeSymbol(Quizz.Operationtype) << endl;
	cout << "Number Of Right Answers: " << Quizz.NumberOfRightQuestion << endl;
	cout << "Number Of Wrong Answers: " << Quizz.NumberOfWrongQuestion << endl;

	cout << "\n_____________________________\n\n";
}

void PlayMathGame() {
	stQuizz Quizz;
	Quizz.NumberOfQuestoin = ReadNumberOfQuestions();
	Quizz.QuestionLevel = ReadQuestoinLevel();
	Quizz.Operationtype = ReadOperationType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzFinalResult(Quizz);
}

void ReSetScreen() {
	system("cls");
	system("color 0F");
}
void StartGame() {
	char PlayAgain = 'Y';
	do
	{
		ReSetScreen();
		PlayMathGame();

		cout << "\n Do you want play again? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();

}
