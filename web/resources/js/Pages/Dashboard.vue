<template>
    <Head title="Dashboard" />

    <AuthenticatedLayout>
        <template #header>
            <h2 class="text-xl font-semibold leading-tight text-gray-800">
                Nazwa Przedmiotu
            </h2>
        </template>

        <div class="max-w-7xl mx-auto py-6 px-4 sm:px-6 lg:px-8 grid grid-cols-2 gap-6">
            <div class="bg-white overflow-x-auto p-5 border border-stone-200 rounded-2xl flex items-center gap-10 min-h-[254px]">
                <div class="relative">
                    <svg width="208" height="208" viewBox="0 0 208 208" style="transform: rotate(-90deg)">
                        <circle r="80" cx="104" cy="100" fill="transparent" stroke-width="30" class="stroke-[#e1e7fe]"></circle>
                        <circle r="80"
                                cx="104"
                                cy="100"
                                fill="transparent"
                                stroke-linecap="round"
                                stroke-width="30"
                                stroke-dasharray="498.6px"
                                :stroke-dashoffset="progress_state"
                                class="stroke-[#5046e5]"
                        ></circle>
                    </svg>
                    <div class="absolute top-1/2 left-1/2 -translate-x-1/2 -translate-y-1/2 text-center text-gray-700 font-semibold text-2xl">
                        {{ students_percent }}%
                    </div>
                </div>
                <div class="grow">
                    <h2 class="font-semibold text-xl mb-6">Studenci w sali</h2>
                    <p class="font-semibold text-6xl mb-6"><span class="text-[#5046e5]">{{ visits.length }}</span><span class="text-3xl">/{{ expectedStudentsCount }}</span></p>
                    <div class="rounded-2xl bg-gray-200 p-2 flex items-center text-sm">
                        <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="size-4 mr-1">
                            <path stroke-linecap="round" stroke-linejoin="round" d="M12 6v6h4.5m4.5 0a9 9 0 1 1-18 0 9 9 0 0 1 18 0Z" />
                        </svg>

                        Czas od rozpoczęcia zajęcia:

                        {{ formatted_time_class }}
                    </div>
                </div>
            </div>

            <div v-if="!isClassStarted" class="bg-white overflow-x-auto p-5 border border-stone-200 rounded-2xl">
                <h2 class="font-semibold text-xl mb-6">
                    Rozpocząć nowe zajęcie
                </h2>

                <div class="grid grid-cols-2 gap-6">
                    <div>
                        <label class="font-medium mb-2 text-gray-700 block">
                            Nazwa grupy
                        </label>

                        <input v-model="groupName" @input="updateSettings" class="border border-gray-300 rounded-xl h-[52px] px-4 block mb-6 w-full focus:border-[#5046e5] transition duration-200 focus:outline-3 focus:outline-offset-0 focus:outline-[#e1e7fe]" placeholder="Grupa 111">
                    </div>
                    <div>
                        <label class="font-medium mb-2 text-gray-700 block">
                            Oczekiwana liczba studentów
                        </label>

                        <input v-model="expectedStudentsCount" @input="updateSettings" class="border border-gray-300 rounded-xl h-[52px] px-4 block mb-6 w-full focus:border-[#5046e5] transition duration-200 focus:outline-3 focus:outline-offset-0 focus:outline-[#e1e7fe]">
                    </div>
                </div>
                <button @click.prevent="resetVisitors" class="bg-[#5046e5] w-full text-white text-lg font-medium rounded-xl h-[52px] transition duration-200 hover:bg-[#453ccc]">
                    Start
                </button>
            </div>
            <div v-else class="bg-white overflow-x-auto p-5 border border-stone-200 rounded-2xl flex flex-col items-center justify-center gap-6">
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="size-10 text-[#5046e5]">
                    <path stroke-linecap="round" stroke-linejoin="round" d="M9 12.75 11.25 15 15 9.75M21 12a9 9 0 1 1-18 0 9 9 0 0 1 18 0Z" />
                </svg>
                <h2 class="font-semibold text-xl mb-6">
                    Zajęcie grupy {{ groupName }} zostało pomyślnie rozpoczęte
                </h2>
                <div class="group w-full grid grid-cols-2 gap-6">
                    <button @click.prevent="stopClass" class="border border-red-700 w-full text-red-700 text-lg font-medium rounded-xl h-[52px] transition duration-200 hover:bg-red-900 hover:text-white hover:border-red-900">
                        Zakończyć zajęcie
                    </button>
                    <button @click.prevent="restartClass" class="bg-[#5046e5] w-full text-white text-lg font-medium rounded-xl h-[52px] transition duration-200 hover:bg-[#453ccc]">
                        Rozpocząć ponownie
                    </button>
                </div>
            </div>
        </div>

        <div class="max-w-7xl mx-auto py-6 px-4 sm:px-6 lg:px-8">
            <div class="bg-white rounded-2xl border border-stone-200 overflow-x-auto">
                <div class="py-4 px-6 font-semibold text-xl border-b border-stone-200">
                    Studenci
                </div>
                <table class="w-full whitespace-nowrap">
                    <thead>
                        <tr class="text-left font-bold">
                            <th class="py-2 px-6 bg-[#f9fbfc]">ID</th>
                            <th class="py-2 px-6 bg-[#f9fbfc]">Hash</th>
                            <th class="py-2 px-6 bg-[#f9fbfc]">Name</th>
                            <th class="py-2 px-6 bg-[#f9fbfc]">Date</th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr
                            v-for="visit in visits"
                            :key="visit.id"
                            class="hover:bg-gray-100 focus-within:bg-gray-100"
                        >
                            <td class="border-t p-5 font-bold">
                                {{ visit.id }}
                            </td>
                            <td class="border-t p-5">
                                {{  visit.hash }}
                            </td>
                            <td class="border-t p-5">-</td>
                            <td class="w-px border-t p-5">
                                {{ formattedDate(visit.created_at) }}
                            </td>
                        </tr>
                        <tr v-if="visits.length === 0">
                            <td class="px-6 py-4 border-t" colspan="4">
                                No visits found.
                            </td>
                        </tr>
                    </tbody>
                </table>
            </div>
        </div>
    </AuthenticatedLayout>
</template>

<script>
import AuthenticatedLayout from "@/Layouts/AuthenticatedLayout.vue";
import { Head } from "@inertiajs/vue3";

export default {
    components: {
        AuthenticatedLayout,
        Head,
    },

    props: {
        visitsOnServer: Object,
    },

    data: () => ({
        visits: [],
        expectedStudentsCount: parseInt(localStorage.getItem('expected_students_count')) || 20,
        groupName: localStorage.getItem('group_name') || "",
        timer: null,
        timeClass: 0,
        isClassStarted: false
    }),

    computed: {
        progress_state() {
            return 498.6 - (this.students_percent * 498.6) / 100;
        },
        students_percent() {
            const percent = (this.visits.length * 100) / this.expectedStudentsCount;
            return Math.min(100, Math.max(Math.round(percent), 0));
        },
        formatted_time_class() {
            const minutes = Math.floor(this.timeClass / 60).toString().padStart(2, '0');
            const seconds = (this.timeClass % 60).toString().padStart(2, '0');
            return `${minutes}:${seconds}`;
        }
    },

    methods: {
        formattedDate(date) {
            return this.$date(date);
        },
        resetVisitors() {
            this.$inertia.post(route('visitors.reset'));
            this.visits = [];
            this.startClass();
        },
        updateSettings() {
            localStorage.setItem('expected_students_count', this.expectedStudentsCount);
            localStorage.setItem('group_name', this.groupName);
        },
        startClass() {
            if (this.isClassStarted) return;
            this.isClassStarted = true;
            this.timer = setInterval(() => {
                this.timeClass++;
            }, 1000)
        },
        stopClass() {
            this.isClassStarted = false;
            clearInterval(this.timer);
            this.timeClass = 0;
        },
        restartClass() {
            clearInterval(this.timer);
            this.timeClass = 0;
            this.timer = setInterval(() => {
                this.timeClass++;
            }, 1000)
        }
    },

    created() {
        Echo.private(`visits`).listen("VisitCreated", (e) => {
            this.visits.unshift(e.visit);
        });
    },

    mounted() {
        this.visits = [...this.visitsOnServer];
    },
};
</script>
