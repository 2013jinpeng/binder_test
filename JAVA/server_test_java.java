import android.util.Log;
import android.os.ServiceManager;

public class server_test_java{
  // 程序的入口
  public static void main(String args[]){
    // 向控制台输出信息
    //System.out.println("Hello World!");
	  
	 ServiceManager.addService("Hello", new HelloService());
	 
	 while (true)
     {
        try {
         	Thread.sleep(100);
       	} catch (Exception e){}
     }
  }
}

