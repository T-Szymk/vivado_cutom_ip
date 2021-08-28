#include <cstdint>

#include "xparameters.h"
#include "xil_io.h"

#define MY_PWM  XPAR_MY_PWM_CORE_0_S00_AXI_BASEADDR
#define MY_GPIO XPAR_GPIO_IP_0_S00_AXI_BASEADDR

#define PWM0 MY_PWM + 0x00
#define PWM1 MY_PWM + 0x04
#define PWM2 MY_PWM + 0x08
#define PWM3 MY_PWM + 0x0c

#define GPIO_IN  MY_GPIO + 0x00
#define GPIO_OUT MY_GPIO + 0x04
#define GPIO_OE  MY_GPIO + 0x08

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

void init() {

	Xil_Out32(PWM0, 0x0);
	Xil_Out32(PWM1, 0x0);
	Xil_Out32(PWM2, 0x0);
	Xil_Out32(PWM3, 0x0);

	Xil_Out32(GPIO_OUT, 0x0);
    Xil_Out32(GPIO_OE,  0x0);
}

int main() {

    pwm_data PWM_DATA;

    uint32_t PWM_val = 0;
    volatile uint32_t GPIO_val = 0;

    init();

    while(1){

        Xil_Out32(PWM0, PWM_DATA.num[0]);
        Xil_Out32(PWM1, PWM_DATA.num[1]);
        Xil_Out32(PWM2, PWM_DATA.num[2]);

        GPIO_val = Xil_In32(GPIO_IN);

        if (Xil_In32(GPIO_IN) & 0x01) {
        	PWM_val = max_counter;
        } else {
        	PWM_val = 0;
        }

        Xil_Out32(PWM3, PWM_val);

        PWM_DATA.pwm_increment();

        for(int i=0;i<300000; i++);
    }
}
