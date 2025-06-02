import SwiftUI

struct LogDetailsView: View {
    var selectedLog: Log //the log to display details

    var body: some View {
        VStack(alignment: .leading, spacing: 16) {
            Text("Location: \(selectedLog.location)") //shows the location
                .font(.headline)
            Text("Weather: \(selectedLog.weather)") //shows the weather
                .font(.subheadline)
            Text("Tide: \(selectedLog.tide) ft") //shows the tide level
                .font(.subheadline)
            Text("Time: \(formattedTime(selectedLog.time))") //shows the time
                .font(.subheadline)

            if selectedLog.fishCaught {
                Text("Fish Caught: Yes") //fish caught info
                    .font(.subheadline)
                if let species = selectedLog.species {
                    Text("Species: \(species)") //species of the fish
                        .font(.subheadline)
                }
                if let weight = selectedLog.weight {
                    Text("Weight: \(weight, specifier: "%.2f") lbs") //weight of the fish
                        .font(.subheadline)
                }
            } else {
                Text("Fish Caught: No") //no fish caught
                    .font(.subheadline)
            }

            Spacer() //pushes content up
        }
        .padding()
        .navigationTitle("Log Details") //title
    }

    //formats time
    func formattedTime(_ date: Date) -> String {
        let formatter = DateFormatter()
        formatter.timeStyle = .short
        formatter.dateStyle = .none
        return formatter.string(from: date)
    }
}
