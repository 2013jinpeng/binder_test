import android.util.Log;
import android.os.ServiceManager;
import android.os.IBinder;

public class client_test_java{
  // 程序的入口
  public static void main(String args[]){
    // 向控制台输出信息
    //System.out.println("Hello World!");
	  
	  IBinder binder = ServiceManager.getService("Hello");	  
	  if(binder == null) {
		  System.out.println("fail to getService HelloService");
		  return;
	  }
	  
	  IHelloService svr = IHelloService.Stub.asInterface(binder);
	  if(svr == null) {
		  System.out.println("fail to asInterface binder");
		  return;
	  }
	  
	  try {
			svr.hello();
			int cnt = svr.say_hello_to("my java");
			System.out.println("cnt:"+cnt);
    } catch (Exception e){}
	  
	  
  }
}

