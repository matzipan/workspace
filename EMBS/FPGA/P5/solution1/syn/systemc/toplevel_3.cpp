#include "toplevel.h"
#include "AESL_pkg.h"

using namespace std;

namespace ap_rtl {

void toplevel::thread_hdltv_gen() {
    const char* dump_tv = std::getenv("AP_WRITE_TV");
    if (!(dump_tv && string(dump_tv) == "on")) return;

    wait();

    mHdltvinHandle << "[ " << endl;
    mHdltvoutHandle << "[ " << endl;
    int ap_cycleNo = 0;
    while (1) {
        wait();
        const char* mComma = ap_cycleNo == 0 ? " " : ", " ;
        mHdltvinHandle << mComma << "{"  <<  " \"ap_rst\" :  \"" << ap_rst.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"input_V_V_dout\" :  \"" << input_V_V_dout.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"input_V_V_empty_n\" :  \"" << input_V_V_empty_n.read() << "\" ";
        mHdltvoutHandle << mComma << "{"  <<  " \"input_V_V_read\" :  \"" << input_V_V_read.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"output_V_V_din\" :  \"" << output_V_V_din.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"output_V_V_full_n\" :  \"" << output_V_V_full_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"output_V_V_write\" :  \"" << output_V_V_write.read() << "\" ";
        mHdltvinHandle << "}" << std::endl;
        mHdltvoutHandle << "}" << std::endl;
        ap_cycleNo++;
    }
}

}

