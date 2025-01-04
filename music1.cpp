#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

class Song {
public:
    string title;
    string artist;
    string audioFormat;
    bool isFavorite;

    Song(string t, string a, string af) : title(t), artist(a), audioFormat(af), isFavorite(false) {}
};

class MusicPlayer {
private:
    vector<Song> playlist;
    int currentSongIndex;
    bool isPlaying;
    bool isPaused;
    int equalizerSetting;

public:
    MusicPlayer() : currentSongIndex(-1), isPlaying(false), isPaused(false), equalizerSetting(5) {}

    void addSong(string title, string artist, string audioFormat) {
        playlist.push_back(Song(title, artist, audioFormat));
    }

    void showPlaylist() {
        if (playlist.empty()) {
            cout << "No songs in playlist.\n";
        } else {
            cout << "Playlist:\n";
            for (int i = 0; i < playlist.size(); ++i) {
                cout << i + 1 << ". " << playlist[i].title << " - " << playlist[i].artist << " [" << playlist[i].audioFormat << "]";
                if (playlist[i].isFavorite) {
                    cout << " (Favorite)";
                }
                cout << endl;
            }
        }
    }

    void searchSong(string search) {
        bool found = false;
        for (const auto &song : playlist) {
            if (song.title.find(search) != string::npos || song.artist.find(search) != string::npos) {
                cout << "Found: " << song.title << " by " << song.artist << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No song found matching: " << search << endl;
        }
    }

    void play() {
        if (playlist.empty()) {
            cout << "No songs to play.\n";
            return;
        }

        if (currentSongIndex == -1) {
            cout << "No song selected to play.\n";
            return;
        }

        isPlaying = true;
        isPaused = false;
        cout << "Playing: " << playlist[currentSongIndex].title << " by " << playlist[currentSongIndex].artist << endl;
        showEqualizer();
        simulateAudioPlayback();
    }

    void pause() {
        if (isPlaying && !isPaused) {
            isPaused = true;
            cout << "Paused: " << playlist[currentSongIndex].title << endl;
        }
        else if (isPaused) {
            cout << "Already paused.\n";
        }
        else {
            cout << "Nothing is playing to pause.\n";
        }
    }

    void stop() {
        if (isPlaying) {
            isPlaying = false;
            isPaused = false;
            cout << "Stopped: " << playlist[currentSongIndex].title << endl;
        } else {
            cout << "Nothing is playing to stop.\n";
        }
    }

    void selectSong(int index) {
        if (index >= 1 && index <= playlist.size()) {
            currentSongIndex = index - 1;
            cout << "Selected: " << playlist[currentSongIndex].title << endl;
        } else {
            cout << "Invalid song index.\n";
        }
    }

    void toggleFavorite() {
        if (currentSongIndex != -1) {
            playlist[currentSongIndex].isFavorite = !playlist[currentSongIndex].isFavorite;
            cout << "Marked as " << (playlist[currentSongIndex].isFavorite ? "Favorite" : "Not Favorite") << ".\n";
        } else {
            cout << "No song selected to mark as favorite.\n";
        }
    }

    void adjustEqualizer(int setting) {
        if (setting >= 0 && setting <= 10) {
            equalizerSetting = setting;
            cout << "Equalizer adjusted to setting: " << equalizerSetting << endl;
        } else {
            cout << "Invalid equalizer setting. Choose a value between 0 and 10.\n";
        }
    }

private:
    void simulateAudioPlayback() {
        cout << "Simulating audio playback..." << endl;
        this_thread::sleep_for(chrono::seconds(3));
        if (isPlaying) {
            cout << "Audio playback finished." << endl;
        }
    }

    void showEqualizer() {
        cout << "Equalizer Setting: " << equalizerSetting << endl;
    }
};

int main() {
    MusicPlayer player;
    int choice, songChoice, eqSetting;
    string title, artist, audioFormat, search;

    while (true) {
        cout << "\nMusic Player Menu:\n";
        cout << "1. Add Song\n";
        cout << "2. Show Playlist\n";
        cout << "3. Search Song\n";
        cout << "4. Select Song\n";
        cout << "5. Play\n";
        cout << "6. Pause\n";
        cout << "7. Stop\n";
        cout << "8. Mark as Favorite\n";
        cout << "9. Adjust Equalizer\n";
        cout << "10. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                getline(cin, title);
                cout << "Enter artist name: ";
                getline(cin, artist);
                cout << "Enter audio format (e.g., mp3, wav): ";
                getline(cin, audioFormat);
                player.addSong(title, artist, audioFormat);
                break;
            case 2:
                player.showPlaylist();
                break;
            case 3:
                cout << "Enter song or artist to search: ";
                getline(cin, search);
                player.searchSong(search);
                break;
            case 4:
                cout << "Enter song number to select: ";
                cin >> songChoice;
                player.selectSong(songChoice);
                break;
            case 5:
                player.play();
                break;
            case 6:
                player.pause();
                break;
            case 7:
                player.stop();
                break;
            case 8:
                player.toggleFavorite();
                break;
            case 9:
                cout << "Enter equalizer setting (0-10): ";
                cin >> eqSetting;
                player.adjustEqualizer(eqSetting);
                break;
            case 10:
                cout << "Exiting the music player.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}