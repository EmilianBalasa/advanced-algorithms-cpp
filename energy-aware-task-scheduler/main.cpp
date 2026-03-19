#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <stack>
#include <iomanip>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

#define NMax 100005
vector<int> graf[NMax], graftranspus[NMax], rezultate[NMax];
vector<pair<float, int>> comparare[NMax];
stack<int> stiva;

int n, m;
int viz[NMax];
int nr_comp_conexe;
int nr_parts_conex[NMax];

void read()
{

    fin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {

        int x, y;
        fin >> x >> y;
        graf[x].push_back(y);
        graftranspus[y].push_back(x);
    }
}

void dfs(int nod)
{

    viz[nod] = 1;
    for (unsigned int i = 0; i < graf[nod].size(); ++i)
    {

        int vecin = graf[nod][i];

        if (!viz[vecin])
            dfs(vecin);
    }

    stiva.push(nod);
}

void dfs_transpus(int nod)
{

    viz[nod] = 2;
    rezultate[nr_comp_conexe].push_back(nod);

    for (unsigned int i = 0; i < graftranspus[nod].size(); ++i)
    {

        int vecin = graftranspus[nod][i];
        if (viz[vecin] != 2)
            dfs_transpus(vecin);
    }
}

void solve()
{

    for (int i = 0; i <= n; ++i)
        if (!viz[i])
            dfs(i);

    while (!stiva.empty())
    {

        int nod = stiva.top();
        // cout << nod << ' ';

        if (viz[nod] == 1)
        {

            nr_comp_conexe++;
            dfs_transpus(nod);
        }

        stiva.pop();
    }
}

void display()
{

    for (int i = 1; i <= nr_comp_conexe; ++i)
    {

        for (size_t j = 0; j < rezultate[i].size(); ++j)
        {
            nr_parts_conex[i]++;
        }


    }
}

struct info_task
{

    int id;
    float workload, deadline;

} date_tasks[NMax];

struct info_dependencies
{

    int one, two;

} date_dependencies[NMax];

struct info_cores
{

    float speed, power;
    float totaltime = 0.0;
    float total_energy = 0.0;

} date_cores[NMax];

bool comparatie(int prim, int secund)
{
    return prim > secund;
}

int n_o_t, n_o_d, n_o_ct, max_node = -1;

void read_all_data()
{

    fin >> n_o_t;

    for (int i = 0; i < n_o_t; ++i)
    {

        int tid;

        fin >> tid >> date_tasks[tid].workload >> date_tasks[tid].deadline;
        date_tasks[tid].id = tid;
    }

    fin >> n_o_d;

    for (int i = 1; i <= n_o_d; ++i)
    {

        fin >> date_dependencies[i].one >> date_dependencies[i].two;
        graf[date_dependencies[i].one].push_back(date_dependencies[i].two);
        graftranspus[date_dependencies[i].two].push_back(date_dependencies[i].one);

        if (max_node < date_dependencies[i].one)
            max_node = date_dependencies[i].one;
        else if (max_node < date_dependencies[i].two)
            max_node = date_dependencies[i].two;
    }

    fin >> n_o_ct;

    for (int i = 1; i <= n_o_ct; ++i)
    {

        fin >> date_cores[i].speed >> date_cores[i].power;
    }

    n = max_node;
    m = n_o_d;
}

int main()
{

    read_all_data();
    solve();
    display();

    for (int i = 1; i <= nr_comp_conexe; ++i)
    {
        if (rezultate[i].size() > n_o_ct)
        {
            fout << "Scheduling failed. No solution found that meets all deadlines.";
            fout << "\nScheduling fails because the cycle involves more nodes than cores.";
            return 0;
        }
    }

    for (int i = 1; i <= n_o_t; ++i)
    {
        bool can_scheduele = false;
        for (int j = 1; j <= n_o_ct; ++j)
        {
            if (date_tasks[i].workload / date_cores[j].speed <= date_tasks[i].deadline)
            {
                can_scheduele = true;
                break;
            }
        }
        if (!can_scheduele)
        {
            fout << "Scheduling failed. No solution found that meets all deadlines.";
            fout << "\nScheduling fails because the required parallel execution violates deadlines.";
            return 0;
        }
    }

    for (int i = 1; i <= n_o_ct; ++i)
    {
        date_cores[i].totaltime = 0.0;
        date_cores[i].total_energy = 0.0;
    }

    struct input_tbl
    {
        int task_id;
        int core_id;
        float start_time;
        float end_time;
        float energy;
    };
    vector <input_tbl> scheduele;
    float total_energy = 0.0;
    fout << "--- Scheduling Results ---\n";
    fout << "Scheduele Table:\n";
    fout << "TaskID | CoreID | StartTime | EndTime | Energy\n";

    for (int i = 1; i <= nr_comp_conexe; ++i)
    {
        int size_dime = rezultate[i].size();

        if (size_dime > 1)
        {
            vector <int> core_ids;
            for (int cr = 1; cr <= n_o_ct; ++cr)
                core_ids.push_back(cr);

            float best_total_energy = 1000000;
            vector <int> asign_good(size_dime);
            vector <float> start_goid(size_dime), end_good(size_dime);

            do
            {
                bool valid = true;
                float this_total_energy = 0.0;
                vector <float> starts(size_dime), ends(size_dime);

                float earliest_start = 0.0;
                for (int j = 0; j < size_dime; ++j)
                {
                    int task_id = rezultate[i][j];
                    for (int dep : graftranspus[task_id])
                    {
                        if (find(rezultate[i].begin(), rezultate[i].end(), dep) == rezultate[i].end())
                        {

                            float dep_end = 0.0;
                            for (int cc = 1; cc <= n_o_ct; ++cc)
                            {
                                dep_end = max(dep_end, date_cores[cc].totaltime);
                            }
                            earliest_start = max(earliest_start, dep_end);

                        }
                    }
                }

                for (int j = 0; j < size_dime; ++j)
                {
                    int task_id = rezultate[i][j];
                    int core = core_ids[j];
                    float exec_time = date_tasks[task_id].workload / date_cores[core].speed;
                    float start_time = max(date_cores[core].totaltime, earliest_start);
                    float end_time = start_time + exec_time;
                    float energy = exec_time * date_cores[core].power;

                    if (end_time > date_tasks[task_id].deadline)
                    {
                        valid = false;
                        break;
                    }
                    this_total_energy += energy;
                    starts[j] = start_time;
                    ends[j] = end_time;
                }

                if (valid && this_total_energy < best_total_energy)
                {
                    best_total_energy = this_total_energy;
                    for (int j = 0; j < size_dime; ++j)
                        asign_good[j] = core_ids[j];
                    start_goid = starts;
                    end_good = ends;
                }
            } while (next_permutation(core_ids.begin(), core_ids.begin() + size_dime));

            if (best_total_energy == 1000000)
            {
                fout << "Scheduling failed. No solution found that meets all deadlines.\n";
                fout << "No valid assignment for SCC " << i << ".\n";
                return 0;
            }

            for (int j = 0; j < size_dime; ++j)
            {
                int task_id = rezultate[i][j];
                int core = asign_good[j];
                float exec_time = date_tasks[task_id].workload / date_cores[core].speed;
                float start_time = start_goid[j];
                float end_time = end_good[j];
                float energy = exec_time * date_cores[core].power;

                date_cores[core].totaltime = end_time;
                date_cores[core].total_energy += energy;
                total_energy += energy;

                fout << task_id << " | " << (core - 1) << " | "
                     << fixed << setprecision(2) << start_time << " | "
                     << end_time << " | " << energy << "\n";
            }
        }
        else
        {

            int task_id = rezultate[i][0];
            int best_core = -1;
            float min_energy = 1000000;
            float best_start = 0, best_end = 0;

            for (int c = 1; c <= n_o_ct; ++c)
            {
                float exec_time = date_tasks[task_id].workload / date_cores[c].speed;
                float start_time = date_cores[c].totaltime;
                float end_time = start_time + exec_time;
                float energy = exec_time * date_cores[c].power;

                if (end_time <= date_tasks[task_id].deadline && energy < min_energy)
                {
                    min_energy = energy;
                    best_core = c;
                    best_start = start_time;
                    best_end = end_time;
                }
            }

            if (best_core == -1)
            {
                if (task_id != 0)
                {
                    fout << "Scheduling failed. No solution found that meets all deadlines.\n";
                    return 0;
                }

                continue;
            }

            date_cores[best_core].totaltime = best_end;
            date_cores[best_core].total_energy += min_energy;
            total_energy += min_energy;

            fout << task_id << " | " << (best_core - 1) << " | "
                 << fixed << setprecision(2) << best_start << " | "
                 << best_end << " | " << min_energy << "\n";
        }
    }

    fout << "Minimum Total Energy Consumed: " << fixed << setprecision(2) << total_energy << "\n";

    return 0;
}