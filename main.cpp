/**
 * Name: drogon_dox
 * Date: 2025-04-10
 * Description: utility to generate restful api documentation from drogon projects
 * Author: Gabriel Espinoza <virtuoso.sdc@gmail.com>
 */

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    // Use filesystem to find Restful*Ctrl.h files
    vector<filesystem::path> restful_controllers;
    if (argc < 2) {
        cerr << "Please provide a directory path" << endl;
        return 1;
    }
    
    filesystem::path dir_path = argv[1];
    if (!filesystem::exists(dir_path)) {
        cerr << "Directory does not exist: " << dir_path << endl;
        return 1;
    }

    for (const auto& entry : filesystem::recursive_directory_iterator(dir_path)) {
        if (entry.is_regular_file()) {
            string filename = entry.path().filename().string();
            if (filename.starts_with("Restful") && filename.ends_with("Ctrl.h")) {
                restful_controllers.push_back(entry.path());
            }
        }
    }
    // Store API endpoint information
    struct Endpoint {
        string function;
        string path;
        string methods;
    };
    vector<Endpoint> endpoints;

    // Scan each controller file
    for (const auto& controller : restful_controllers) {
        ifstream file(controller);
        string line;
        
        while (getline(file, line)) {
            // Skip commented lines
            if (line.find("//") != string::npos) {
                continue;
            }
            
            // Look for ADD_METHOD_TO macro
            size_t pos = line.find("ADD_METHOD_TO");
            if (pos != string::npos) {
                // Extract content between parentheses
                size_t start = line.find('(', pos);
                size_t end = line.find(')', start);
                if (start != string::npos && end != string::npos) {
                    string args = line.substr(start + 1, end - start - 1);
                    
                    // Split arguments by comma
                    vector<string> tokens;
                    stringstream ss(args);
                    string token;
                    while (getline(ss, token, ',')) {
                        // Trim whitespace
                        token.erase(0, token.find_first_not_of(" "));
                        token.erase(token.find_last_not_of(" ") + 1);
                        tokens.push_back(token);
                    }
                    
                    // Create endpoint if we have at least function and path
                    if (tokens.size() >= 2) {
                        Endpoint endpoint;
                        endpoint.function = tokens[0];
                        endpoint.path = tokens[1];
                        
                        // Add remaining tokens as methods
                        for (size_t i = 2; i < tokens.size(); i++) {
                            endpoint.methods += " ";
							endpoint.methods += tokens[i];
                        }
                        
                        endpoints.push_back(endpoint);
                    }
                }
            }
        }
    }
    // Create API documentation file
    ofstream doc_file("myapidoc.md");
    doc_file << "# API Documentation\n\n";
    doc_file << "This document describes all available API endpoints.\n\n";
    doc_file << "## Endpoints\n\n";
	for (const auto& endpoint : endpoints) {
		doc_file << "### " << endpoint.path  << "\n\n";
		doc_file << "Called function: " << endpoint.function << "\n\n";
		doc_file << "Allowed methods: " << endpoint.methods << "\n\n";
	}
    doc_file.close();
}
