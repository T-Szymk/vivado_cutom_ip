#include "xparameters.h"
#include "xil_io.h"

#define MY_PWM XPAR_MY_PWM_CORE_0_S00_AXI_BASEADDR

constexpr int max_counter = 1024;

class pwm_data {
public:
	pwm_data() = default;
	void pwm_increment();

	int num[4] = {0};

private:
	int incr_arr[4] = {1, 2, 4, 8};

};

void pwm_data::pwm_increment() {

	for (int i = 0; i < 4; i++) {
	  num[i] += incr_arr[i];
	  if (num[i] > max_counter) {
		  num[i] = 0;
	  }
	}
}

int main() {

    pwm_data PWM_DATA;

    while(1){

        Xil_Out32(MY_PWM, PWM_DATA.num[0]);
        Xil_Out32((MY_PWM+4), PWM_DATA.num[1]);
        Xil_Out32((MY_PWM+8), PWM_DATA.num[2]);
        Xil_Out32((MY_PWM+12), PWM_DATA.num[3]);

        PWM_DATA.pwm_increment();

        for(int i=0;i<300000; i++);
    }
}
