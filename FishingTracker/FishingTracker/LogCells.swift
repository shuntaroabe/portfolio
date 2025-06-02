//
//  LogCells.swift
//  FishingTracker
//
//  Created by Shuntaro Abe on 12/9/24.
//

import Foundation
import SwiftUI

@Observable class LogCells: Identifiable {
    var logs: [Log]

    init(logs: [Log] = []) {
        self.logs = logs
    }
}
