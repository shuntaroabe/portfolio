import SwiftUI

struct LogsOverviewView: View {
    @Binding var logCells: LogCells //shared log data
    @State private var stackPath = NavigationPath() //for navigation stack

    var body: some View {
        NavigationStack(path: $stackPath) {
            List {
                ForEach($logCells.logs, id: \.self) { $log in
                    NavigationLink(value: log) {
                        ListCell(log: log) //cell for each log
                    }
                }
                .onDelete(perform: deleteLogs) //delete
                .onMove(perform: moveLogs) //reorder logs
            }
            .navigationDestination(for: Log.self) { log in
                LogDetailsView(selectedLog: log) //go to details view
            }
            .navigationTitle(Text("Logs Overview")) //screen title
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    EditButton() //button for edit mode
                }
            }
        }
    }

    //deletes selected logs
    func deleteLogs(at offsets: IndexSet) {
        logCells.logs.remove(atOffsets: offsets)
    }

    //moves logs around in the list
    func moveLogs(from source: IndexSet, to destination: Int) {
        logCells.logs.move(fromOffsets: source, toOffset: destination)
    }

    struct ListCell: View {
        var log: Log //log data for the cell
        var body: some View {
            HStack {
                VStack(alignment: .leading) {
                    Text(log.location) //location of log
                        .font(.headline)
                    Text("Time: \(formattedTime(log.time))") //formatted time
                        .font(.subheadline)
                        .foregroundColor(.gray)
                    Text("Tide: \(log.tide) ft") //tide level
                        .font(.subheadline)
                }
                Spacer()
                Circle() //indicator for fish caught
                    .fill(log.fishCaught ? Color.green : Color.red)
                    .frame(width: 20, height: 20)
            }
            .padding()
        }

        //formats the time for display
        func formattedTime(_ date: Date) -> String {
            let formatter = DateFormatter()
            formatter.timeStyle = .short
            formatter.dateStyle = .none
            return formatter.string(from: date)
        }
    }
}
