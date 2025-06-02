import SwiftUI

struct NewLogView: View {
    @Environment(\.dismiss) var dismiss //to close the view
    @Binding var logCells: LogCells //shared log data

    //state variables for user input
    @State private var location: String = "" //location input
    @State private var weather: String = "Sunny" //default weather
    @State private var tide: Int = 0 //default tide level
    @State private var time: Date = Date() //current time
    @State private var fishCaught: Bool = false //toggle for fish caught
    @State private var species: String = "" //species input
    @State private var weight: String = "" //weight input

    //weather options for picker
    let weatherOptions = ["Sunny", "Cloudy", "Rainy", "Stormy"]

    var body: some View {
        NavigationStack {
            Form {
                Section(header: Text("Location")) {
                    TextField("Enter location", text: $location) //location input field
                }

                Section(header: Text("Weather")) {
                    Picker("Select weather", selection: $weather) { //weather picker
                        ForEach(weatherOptions, id: \.self) { option in
                            Text(option)
                        }
                    }
                    .pickerStyle(SegmentedPickerStyle()) //picker style
                }

                Section(header: Text("Tide (ft)")) {
                    Picker("Tide level", selection: $tide) { //tide picker
                        ForEach(-3...3, id: \.self) { level in
                            Text("\(level) ft").tag(level) //tide levels
                        }
                    }
                    .pickerStyle(WheelPickerStyle()) //picker style
                }

                Section(header: Text("Time")) {
                    DatePicker("Select time", selection: $time, displayedComponents: .hourAndMinute) //time picker
                }

                Section(header: Text("Catch Details")) {
                    Toggle("Fish Caught", isOn: $fishCaught) //toggle for fish caught

                    if fishCaught {
                        TextField("Species", text: $species) //species input field
                        TextField("Weight (lbs)", text: $weight) //weight input field
                            .keyboardType(.decimalPad) //number pad for decimals
                    }
                }

                Button(action: saveLog) { //button to save log
                    Text("Save Log")
                        .font(.headline)
                        .foregroundColor(.white)
                        .frame(maxWidth: .infinity)
                        .padding()
                        .background(Color.blue)
                        .cornerRadius(10)
                }
                .padding(.vertical)
                .disabled(location.isEmpty) //disable if location empty
            }
            .navigationTitle("New Log") //title for the view
        }
    }

    //saves the new log and dismisses the view
    private func saveLog() {
        guard !location.isEmpty else { return } //make sure location is entered
        let weightValue = Double(weight) //convert weight to Double

        let newLog = Log(
            id: UUID(),
            location: location,
            weather: weather,
            tide: tide,
            time: time,
            fishCaught: fishCaught,
            species: fishCaught ? species : nil, //species only if fish caught
            weight: fishCaught ? weightValue : nil //weight only if fish caught
        )

        logCells.logs.append(newLog) //add new log to shared data

        dismiss() //close the view
    }
}


#Preview {
    NewLogView(logCells: .constant(LogCells()))
}

