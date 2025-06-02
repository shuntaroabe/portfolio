//
//  Log.swift
//  FishingTracker
//
//  Created by Shuntaro Abe on 12/8/24.
//

import Foundation

// single fishing log
struct Log: Hashable, Codable, Identifiable {
    var id: UUID //unique ID for each log
    var location: String //location
    var weather: String //weather conditions
    var tide: Int //tide level
    var time: Date //time of the log
    var fishCaught: Bool //whether a fish was caught
    var species: String? //species of fish
    var weight: Double? //weight of the fish
}
