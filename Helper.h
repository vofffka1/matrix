# include <vector>
# include <algorithm>
# include <fstream>
# include <utility>

typedef std::vector<int> IntVec;
typedef std::vector<double> DoubleVec;
typedef std::vector<IntVec> IntMat;

class Helper 
	{
	public :
		Helper() {};
		Helper(const IntMat &A,double eps=0.001)
			{
			auto Size = A.size();
			std::size_t MaxIterations = 100;
			double summ=0,e,d,d0;
			DoubleVec w0 = DoubleVec(Size,0);
			DoubleVec w0norm = DoubleVec(Size,0);
			DoubleVec w = DoubleVec(Size,0);
			std::size_t i,j,iter=0;

			for (i=0;i<Size;i++) w0[i]=0;
			w0[0]=1;
			do {
				for (i=0;i<Size;i++) summ=summ+w0[i]*w0[i];
				d0=sqrt(summ);
				for (i=0;i<Size;i++) w0norm[i]=w0[i]/d0;
				for (i=0;i<Size;i++){
					w[i]=0;
					for (j=0;j<Size;j++) w[i]=w[i]+A[i][j]*w0norm[j];
					}
				summ=0;
				for (i=0;i<Size;i++) summ=summ+w[i]*w[i];
				d=sqrt(summ);
				e=fabs(d-d0);
				for (i=0;i<Size;i++) w0[i]=w[i];
				summ=0;
				iter++;
				Results.push_back(std::make_pair(iter,d));
				}
			while(e>eps && iter < 100); 
			EigenVec = w0norm;
			EigenValue = d;
			is_compute = true;
			};

		static IntMat get_matrix(std::ifstream &in)
			{ 
			std::size_t Size;
			in>>Size;
			IntMat R = IntMat(Size,IntVec(Size,0));
			for (std::size_t i=0;i<Size;i++)
				for (std::size_t j=0;j<Size;j++)
					in>>R[i][j];
			return R;
			}

		DoubleVec EigenVec;
		double EigenValue;
		std::vector<std::pair<std::size_t,double>> Results;
		bool is_compute;
	};
