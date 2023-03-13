#include <iostream>
#include <ctime>
#define sigmoid(x) ( 1.0/(1.0+exp(-(x))) ) // sigmoid

using namespace std;

class Neuron {
    //private�� ����
    int input_num; //��ǲ
    double output; //�ƿ�ǲ
    double Alpha; //���� = �ΰ������
    double *input_weight; //��ǲ�� ���� ����ġ(�ó��� ���ᰭ��) 
    double *weight_error; //����ġ ����
    // �迭��� �����ͷ� ����
public:
    Neuron(int input, double alpha) //������ �Լ�
    {
        input_num = input;
        Alpha = alpha;
        input_weight = new double[input + 1]; //��ġ���� ����� ��� ����ġ(w3) �Է� ��� => +1, �����Ҵ�
        weight_error = new double[input + 1]; //��ġ���� ����� ��� ����ġ(w3) �Է� ��� => +1, �����Ҵ�

        for (int i = 0; i < input + 1; i++)
        {
            input_weight[i] = ((double)rand() /RAND_MAX)-1; //0.0 ~ 1.0������ �� -1 => ������ ����ġ(-1~1)�� ����
            weight_error[i] = 0.0; //����ġ���� �ʱ�ȭ
        }

    }
    ~Neuron()
    {
        delete[] input_weight;
        delete[] weight_error;
    }

    double work(double input[]) //�Է½�ȣ �迭�� ���ڷ� ����, �ñ׸��̵� �Լ��� �̿��Ͽ� �� ���
    {
        double sum = 0;
        for (int i = 0; i < input_num; i++)
        {
            sum += input[i] * input_weight[i]; //sum += ��ǲ X ����ġ
        }
        sum += input_weight[input_num] * 1.0; //sum +=�������ġ,����

        return sigmoid(sum);
    }
    //�н��Լ�, ������ �پ��� ��������
    void learn(double input[], double target) //�н��Լ�, neuron->learn(sample_input[j], sample_output[j]); �̷��� ȣ���ϱ� ������ input�� �迭��, target �ϳ��� ������ �޾Ƶ���
    {
        output = work(input); //���
        double output_error = output - target; //���� = ���-��ǥ

        for (int i = 0; i < input_num; i++)
        {
            weight_error[i] += output_error * input[i]; //����x��ǲ
        }
       
        weight_error[input_num] += output_error * 1.0; //�������ġ,����

    }

    

    void fix() //����ġ �����Լ�
    {
        for (int i = 0; i< input_num + 1; i++)
        {
            input_weight[i] -= Alpha * weight_error[i] *output * (1 - output);; //����(=�ΰ���, �н���(learning rate)����), output * (1 - output)->����, ���Ŀ� ���� ���� ����ġ ����
            weight_error[i] = 0.0;
        }
    }
};

int main() {
    srand((unsigned)time(NULL));	// ���� ����ġ�� ���Ƿ� ���ϱ� ���� ����.

    // ���� Ŭ���� ������.
    // Neuron(int num_of_input, double alpha) //���Ĵ� �ΰ��� ���(=0.1)
                  //(�Է��� ��, learning rate)
    Neuron* neuron = new Neuron(2, 0.1);

    // Sample Sets for AND
   // double sample_input[4][2] = { {0,0},{0,1},{1,0},{1,1} };
   // double sample_output[4] = { 0, 0, 0, 1 };
    

   
     // Sample Sets for OR
    //double sample_input[4][2] = { {0,0},{0,1},{1,0},{1,1} };
   // double sample_output[4] = { 0, 1, 1, 1 };
   

    // Sample Sets for NOT, NOT������ AND�� ORó�� ���ϼ��� �ֱ� ���� �Է°� �ϳ��� �ƴ� �Է°� �ΰ� ��
    double sample_input[4][2] = { {0,0},{0,0},{1,1},{1,1} };
    double sample_output[4] = { 1, 1, 0, 0 };
    
    //AND,OR�õ��� ���� ���ϴ� ���� �� �ּ� Ǯ�� NOT�� �ּ� ó�����ֱ�

    for (int i = 0; i < 5000; i++) {
        for (int j = 0; j < 4; j++) {
            neuron->learn(sample_input[j], sample_output[j]); // �н�
        }
        neuron->fix(); // ����ġ ����

        // Print result //
        if ((i + 1) % 100 == 0) {
            cout << "------ Learn " << i + 1 << " times -----" << endl;
            for (int j = 0; j < 4; j++) {
                cout << sample_input[j][0] << ' ' << sample_input[j][1] << " : "
                    << neuron->work(sample_input[j]) << endl; // �����
            }
        }
    }
    delete neuron;
}
