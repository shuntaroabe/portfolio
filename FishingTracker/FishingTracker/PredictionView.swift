import SwiftUI

struct PredictionView: View {
    @State var identifier = FishingIdentifier() //instance ofML
    @State private var time: Int = 0 //time input from user
    @State private var tide: Int = 0 //tide input from user

    var body: some View {
        VStack(alignment: .center, spacing: 20) {
            Spacer()

            //shows prediction
            Text(self.identifier.prediction.uppercased())
                .font(.system(size: 60))
                .foregroundColor(self.identifier.prediction == "Good" ? .green : .red)

            //shows confidence
            Text("Confidence: \(String(format: "%.2f", self.identifier.confidence))")
                .font(.headline)

            //inputs for time and tide
            VStack(alignment: .leading, spacing: 10) {
                //time input field
                HStack {
                    Text("Time (0-23):")
                        .font(.headline)
                    TextField("Enter time", value: $time, format: .number)
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                        .keyboardType(.numberPad)
                        .frame(width: 100)
                }

                //tide input field
                HStack {
                    Text("Tide (-3 to 3):")
                        .font(.headline)
                    TextField("Enter tide", value: $tide, format: .number)
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                        .keyboardType(.numberPad)
                        .frame(width: 100)
                }
            }
            .padding()

            //button to make prediction
            Button(action: {
                identifier.predict(time: time, tide: tide) //call predict
            }) {
                Text("Predict")
                    .font(.headline)
                    .foregroundColor(.white)
                    .padding()
                    .frame(maxWidth: .infinity)
                    .background(Color.blue)
                    .cornerRadius(10)
            }
            .padding()

            Spacer()
        }
        .padding()
        .navigationTitle("Prediction")
    }
}
