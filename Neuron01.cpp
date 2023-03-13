#include <iostream>
#include <ctime>
#define sigmoid(x) ( 1.0/(1.0+exp(-(x))) ) // sigmoid

using namespace std;

class Neuron {
    //private한 영역
    int input_num; //인풋
    double output; //아웃풋
    double Alpha; //알파 = 민감도상수
    double *input_weight; //인풋에 대한 가중치(시냅스 연결강도) 
    double *weight_error; //가중치 에러
    // 배열대신 포인터로 지정
public:
    Neuron(int input, double alpha) //생성자 함수
    {
        input_num = input;
        Alpha = alpha;
        input_weight = new double[input + 1]; //역치값을 대신할 상수 가중치(w3) 입력 고려 => +1, 동적할당
        weight_error = new double[input + 1]; //역치값을 대신할 상수 가중치(w3) 입력 고려 => +1, 동적할당

        for (int i = 0; i < input + 1; i++)
        {
            input_weight[i] = ((double)rand() /RAND_MAX)-1; //0.0 ~ 1.0까지의 값 -1 => 랜덤의 가중치(-1~1)를 갖음
            weight_error[i] = 0.0; //가중치에러 초기화
        }

    }
    ~Neuron()
    {
        delete[] input_weight;
        delete[] weight_error;
    }

    double work(double input[]) //입력신호 배열을 인자로 받음, 시그모이드 함수를 이용하여 값 출력
    {
        double sum = 0;
        for (int i = 0; i < input_num; i++)
        {
            sum += input[i] * input_weight[i]; //sum += 인풋 X 가중치
        }
        sum += input_weight[input_num] * 1.0; //sum +=상수가중치,편향

        return sigmoid(sum);
    }
    //학습함수, 오차가 줄어드는 방향으로
    void learn(double input[], double target) //학습함수, neuron->learn(sample_input[j], sample_output[j]); 이렇게 호출하기 때문에 input은 배열로, target 하나의 값으로 받아들임
    {
        output = work(input); //출력
        double output_error = output - target; //오차 = 출력-목표

        for (int i = 0; i < input_num; i++)
        {
            weight_error[i] += output_error * input[i]; //오차x인풋
        }
       
        weight_error[input_num] += output_error * 1.0; //상수가중치,편향

    }

    

    void fix() //가중치 수정함수
    {
        for (int i = 0; i< input_num + 1; i++)
        {
            input_weight[i] -= Alpha * weight_error[i] *output * (1 - output);; //알파(=민감도, 학습률(learning rate)조절), output * (1 - output)->기울기, 알파와 기울기 통해 가중치 수정
            weight_error[i] = 0.0;
        }
    }
};

int main() {
    srand((unsigned)time(NULL));	// 최초 가중치를 임의로 정하기 위한 난수.

    // 뉴런 클래스 생성자.
    // Neuron(int num_of_input, double alpha) //알파는 민감도 상수(=0.1)
                  //(입력의 수, learning rate)
    Neuron* neuron = new Neuron(2, 0.1);

    // Sample Sets for AND
   // double sample_input[4][2] = { {0,0},{0,1},{1,0},{1,1} };
   // double sample_output[4] = { 0, 0, 0, 1 };
    

   
     // Sample Sets for OR
    //double sample_input[4][2] = { {0,0},{0,1},{1,0},{1,1} };
   // double sample_output[4] = { 0, 1, 1, 1 };
   

    // Sample Sets for NOT, NOT형식을 AND과 OR처럼 통일성을 주기 위해 입력값 하나가 아닌 입력값 두개 줌
    double sample_input[4][2] = { {0,0},{0,0},{1,1},{1,1} };
    double sample_output[4] = { 1, 1, 0, 0 };
    
    //AND,OR시도할 때는 원하는 샘플 셋 주석 풀고 NOT은 주석 처리해주기

    for (int i = 0; i < 5000; i++) {
        for (int j = 0; j < 4; j++) {
            neuron->learn(sample_input[j], sample_output[j]); // 학습
        }
        neuron->fix(); // 가중치 수정

        // Print result //
        if ((i + 1) % 100 == 0) {
            cout << "------ Learn " << i + 1 << " times -----" << endl;
            for (int j = 0; j < 4; j++) {
                cout << sample_input[j][0] << ' ' << sample_input[j][1] << " : "
                    << neuron->work(sample_input[j]) << endl; // 결과값
            }
        }
    }
    delete neuron;
}
