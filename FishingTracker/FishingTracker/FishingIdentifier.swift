import Foundation
import CoreML

@Observable class FishingIdentifier {
    var prediction = "" //prediction result
    var confidence = 0.0 //confidence score
    var model: FishingML_1 //modle

    init() {
        let config = MLModelConfiguration() // config
        do {
            self.model = try FishingML_1(configuration: config) //load model
        } catch {
            fatalError("Error") //fail if model doesn't load
        }
    }

    func predict(time: Int, tide: Int) {
        do {
            let input = FishingML_1Input(v2: Int64(Int(time)), v3: Int64(Int(tide))) //input for ML model

            let result = try model.prediction(input: input) //get prediction

            if let (label, confidence) = result.v1Probability.max(by: { $0.value < $1.value }) {
                self.prediction = label //store label
                self.confidence = confidence //store confidence
            }
        } catch {
            print("Error making prediction") //fallback for errors
            self.prediction = "Error"
            self.confidence = 0.0
        }
    }
}
