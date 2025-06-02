import SwiftUI

struct HomeView: View {
    @State var logCells = LogCells() //shared log data

    var body: some View {
        NavigationStack {
            VStack {
                Image("AppLogo") //logo at the top
                    .resizable()
                    .scaledToFit()
                    .frame(height: 200)
                    .padding(.top, 50)
                Spacer()

                //buttons for navigation
                VStack(spacing: 20) {
                    NavigationLink(destination: NewLogView(logCells: $logCells)) {
                        Text("Create Log") //goes to new log creation screen
                            .font(.headline)
                            .foregroundColor(.white)
                            .padding()
                            .frame(maxWidth: .infinity)
                            .background(Color.blue)
                            .cornerRadius(10)
                    }
                    
                    NavigationLink(destination: LogsOverviewView(logCells: $logCells)) {
                        Text("Logs Overview") //shows all saved logs
                            .font(.headline)
                            .foregroundColor(.white)
                            .padding()
                            .frame(maxWidth: .infinity)
                            .background(Color.cyan)
                            .cornerRadius(10)
                    }
                    
                    NavigationLink(destination: PredictionView()) {
                        Text("Predict") //opens prediction feature
                            .font(.headline)
                            .foregroundColor(.white)
                            .padding()
                            .frame(maxWidth: .infinity)
                            .background(Color.indigo)
                            .cornerRadius(10)
                    }
                }
                .padding(.horizontal, 20)

                Spacer()
            }
        }
    }
}



#Preview {
    HomeView()
}
