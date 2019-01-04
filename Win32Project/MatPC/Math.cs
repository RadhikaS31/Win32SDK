using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Math
{
    [ClassInterface(ClassInterfaceType.AutoDual)]
    public class Math
    {

        //public int DivisionValue { get; set; }
        //public int MultiplicationValue { get; set; }
        public int ForceValue { get; set; }
        public int ConstantValue { get; set; }
        public int DistanceValue { get; set; }

        public Math()
        {
            //empty
        }

        public int Force(int k, int x)
        {
            ForceValue = (-k) * x;
            MessageBox.Show("Force is :" + ForceValue);
            return ForceValue;
        }

        public int Constant(int f,int x)
        {
            ConstantValue = f / x;
            MessageBox.Show("Constant is :" + ConstantValue);
            return ConstantValue;
        }

        public int Distance(int f, int k)
        {
            DistanceValue = (-f)/k;
            MessageBox.Show("Distance is :" + DistanceValue);
            return DistanceValue;
        }
    }
}
