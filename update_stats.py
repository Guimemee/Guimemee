import os
import urllib.request
import json

# Fetch token from environment
TOKEN = os.getenv("GH_TOKEN")
USERNAME = "Guimemee"

# If not in env, check for a local config file (not committed to git)
if not TOKEN:
    try:
        # Try to read from local file for local execution
        config_path = os.path.join(os.path.dirname(__file__), ".token")
        if os.path.exists(config_path):
            with open(config_path, "r", encoding="utf-8") as f:
                TOKEN = f.read().strip()
    except Exception:
        pass

if not TOKEN:
    raise ValueError("Error: GH_TOKEN environment variable not set, and local .token file not found.")

def fetch_github_api(url, accept_header=None):
    headers = {
        "Authorization": f"token {TOKEN}",
        "User-Agent": "Mozilla/5.0"
    }
    if accept_header:
        headers["Accept"] = accept_header
        
    req = urllib.request.Request(url, headers=headers)
    try:
        with urllib.request.urlopen(req) as response:
            return json.loads(response.read().decode())
    except Exception as e:
        print(f"Error fetching {url}: {e}")
        return None

def main():
    print("Fetching stats from GitHub API...")
    
    # 1. Total Commits (Public & Private)
    commits_data = fetch_github_api(
        f"https://api.github.com/search/commits?q=author:{USERNAME}",
        accept_header="application/vnd.github.cloak-preview+json"
    )
    commits_count = commits_data.get("total_count", 0) if commits_data else 0
    
    # 2. Total Pull Requests (Public & Private)
    prs_data = fetch_github_api(f"https://api.github.com/search/issues?q=author:{USERNAME}+type:pr")
    prs_count = prs_data.get("total_count", 0) if prs_data else 0
    
    # 3. Total Issues (Public & Private)
    issues_data = fetch_github_api(f"https://api.github.com/search/issues?q=author:{USERNAME}+type:issue")
    issues_count = issues_data.get("total_count", 0) if issues_data else 0
    
    # 4. Total Repositories and Stars
    repos_count = 0
    stars_count = 0
    page = 1
    while True:
        repos_data = fetch_github_api(f"https://api.github.com/user/repos?per_page=100&page={page}&type=owner")
        if not repos_data:
            break
        repos_count += len(repos_data)
        stars_count += sum(repo.get("stargazers_count", 0) for repo in repos_data)
        if len(repos_data) < 100:
            break
        page += 1

    print(f"Stats loaded: Commits={commits_count}, PRs={prs_count}, Issues={issues_count}, Repos={repos_count}, Stars={stars_count}")

    # Generate Rank based on commit & PR activity
    total_score = commits_count + (prs_count * 2) + (stars_count * 4)
    if total_score > 300:
        rank = "A+"
    elif total_score > 150:
        rank = "A"
    elif total_score > 50:
        rank = "B+"
    else:
        rank = "B"

    # SVG Template matching Tokyo Night theme
    svg_content = f"""<svg width="495" height="195" viewBox="0 0 495 195" fill="none" xmlns="http://www.w3.org/2000/svg">
  <style>
    .header {{ font: 600 18px 'Segoe UI', Ubuntu, Sans-Serif; fill: #70a5fd; }}
    .stat {{ font: 600 14px 'Segoe UI', Ubuntu, Sans-Serif; fill: #38bdf8; }}
    .label {{ font: 400 14px 'Segoe UI', Ubuntu, Sans-Serif; fill: #a9b1d6; }}
    .rank {{ font: 800 24px 'Segoe UI', Ubuntu, Sans-Serif; fill: #ff9e64; }}
    .rank-label {{ font: 400 10px 'Segoe UI', Ubuntu, Sans-Serif; fill: #7982a9; }}
    .card-bg {{ fill: #1a1b27; rx: 8px; }}
  </style>
  <rect x="0.5" y="0.5" width="494" height="194" class="card-bg" stroke="#e4e2e2" stroke-opacity="0" />
  
  <text x="25" y="35" class="header">Estatísticas do GitHub de {USERNAME}</text>
  
  <g transform="translate(0, 50)">
    <!-- Commits Icon and Text -->
    <g transform="translate(25, 0)">
      <path d="M10.5 8a2.5 2.5 0 11-5 0 2.5 2.5 0 015 0z" fill="#70a5fd"/>
      <path fill-rule="evenodd" d="M10.5 1A7.5 7.5 0 1018 8.5 7.508 7.508 0 0010.5 1zm0 13a5.5 5.5 0 110-11 5.5 5.5 0 010 11z" clip-rule="evenodd" fill="#70a5fd"/>
      <text x="25" y="12" class="label">Total Commits:</text>
      <text x="180" y="12" class="stat">{commits_count}</text>
    </g>

    <!-- PRs Icon and Text -->
    <g transform="translate(25, 25)">
      <path fill-rule="evenodd" d="M7.177 3.073L9.573.677A.25.25 0 0110 .854v4.792a.25.25 0 01-.427.177L7.177 3.427a.25.25 0 010-.354zM3.75 2.5a.75.75 0 100-1.5.75.75 0 000 1.5zm0 1.5a2.25 2.25 0 100-4.5 2.25 2.25 0 000 4.5zm0 10.5a.75.75 0 100-1.5.75.75 0 000 1.5zm0 1.5a2.25 2.25 0 100-4.5 2.25 2.25 0 000 4.5z" clip-rule="evenodd" fill="#70a5fd"/>
      <text x="25" y="12" class="label">Total Pull Requests (c/ Privados):</text>
      <text x="270" y="12" class="stat">{prs_count}</text>
    </g>

    <!-- Issues Icon and Text -->
    <g transform="translate(25, 50)">
      <path fill-rule="evenodd" d="M8 15A7 7 0 108 1a7 7 0 000 14zm0 1A8 8 0 108 0a8 8 0 000 16zM8 4a.75.75 0 01.75.75v4.5a.75.75 0 01-1.5 0v-4.5A.75.75 0 018 4zm0 8a1 1 0 100-2 1 1 0 000 2z" clip-rule="evenodd" fill="#70a5fd"/>
      <text x="25" y="12" class="label">Total Issues:</text>
      <text x="180" y="12" class="stat">{issues_count}</text>
    </g>

    <!-- Repos Icon and Text -->
    <g transform="translate(25, 75)">
      <path fill-rule="evenodd" d="M2 2.5A2.5 2.5 0 014.5 0h8.75a.75.75 0 01.75.75v12.5a.75.75 0 01-.75.75h-2.5a.75.75 0 110-1.5h1.75v-2h-8a1 1 0 00-.714 1.7.75.75 0 01-1.072 1.05A2.495 2.495 0 012 11.5v-9zm10.5-1V9h-8c-.356 0-.694.074-1 .208V2.5a1 1 0 011-1h8z" clip-rule="evenodd" fill="#70a5fd"/>
      <text x="25" y="12" class="label">Total Repositórios:</text>
      <text x="180" y="12" class="stat">{repos_count}</text>
    </g>

    <!-- Stars Icon and Text -->
    <g transform="translate(25, 100)">
      <path d="M8 .25a.75.75 0 01.673.418l1.882 3.815 4.21.612a.75.75 0 01.416 1.279l-3.046 2.97.719 4.192a.75.75 0 01-1.088.791L8 12.347l-3.766 1.98a.75.75 0 01-1.088-.79l.72-4.194L.818 6.374a.75.75 0 01.416-1.28l4.21-.611L7.327.668A.75.75 0 018 .25z" fill="#70a5fd"/>
      <text x="25" y="12" class="label">Estrelas Recebidas:</text>
      <text x="180" y="12" class="stat">{stars_count}</text>
    </g>
  </g>
  
  <!-- Rank Card -->
  <g transform="translate(380, 50)">
    <rect width="90" height="110" rx="8" fill="#16161e" stroke="#2a2b36" stroke-width="1.5" />
    <text x="45" y="30" text-anchor="middle" class="rank-label">NÍVEL GERAL</text>
    <text x="45" y="70" text-anchor="middle" class="rank">{rank}</text>
  </g>
</svg>
"""
    
    # Save the generated SVG
    output_path = os.path.join(os.path.dirname(__file__), "github-stats.svg")
    with open(output_path, "w", encoding="utf-8") as f:
        f.write(svg_content)
    print(f"SVG Stats generated successfully at {output_path}!")

if __name__ == "__main__":
    main()
